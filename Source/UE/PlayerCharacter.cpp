#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "SkillProjectile.h"
#include "DrawDebugHelpers.h"
#include "Monster.h"
#include "SkillEffect.h"
#include "UEGameInstance.h"
#include "UEGamemodeBase.h"
#include "MainWidget.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));

	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_pMesh = GetMesh();

	// 터짐
	//static ConstructorHelpers::FClassFinder<UPlayerAnimInstance> ClassFinder(TEXT("AnimBlueprint'/Game/Player/BP_AuroraAnim.BP_AuroraAnim_C'"));

	//if (ClassFinder.Succeeded())
	//{
	//	GetMesh()->SetAnimInstanceClass(ClassFinder.Class);
	//}

	m_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_pSpringArm->SetupAttachment(RootComponent);

	m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_pCamera->SetupAttachment(m_pSpringArm);


	m_pSpringArm->TargetArmLength = 700.f;
	m_pSpringArm->TargetOffset.Z = 70.f;
	m_pSpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	m_pSpringArm->bDoCollisionTest = false;

	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->MaxWalkSpeed = 3000.f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	m_iAttackCombo = 0;

	m_isAttacking = false;

	m_isSaveAttack = false;

	m_isEvading = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_pAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	UUEGameInstance* pInstance = Cast<UUEGameInstance>(GetGameInstance());
	FSaveCharacterInfo* pInfo = pInstance->Get_CharacterInfo();

	m_eJob = pInfo->Job;
	m_fAttackPoint = pInfo->AttackPoint;
	m_fArmorPoint = pInfo->ArmorPoint;
	m_fAttackRange = pInfo->AttackRange;
	m_fHP = pInfo->HP;
	m_fHPMax = pInfo->HPMax;
	m_fMP = pInfo->MP;
	m_fMPMax = pInfo->MPMax;
	m_iLevel = pInfo->Level;
	m_iExp = pInfo->Exp;
	m_iMoney = pInfo->Money;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("Move_Forward"), this, &APlayerCharacter::Move_Forward);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("Move_Side"), this, &APlayerCharacter::Move_Side);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("Mouse_X"), this, &APlayerCharacter::Mouse_X);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("Mouse_Y"), this, &APlayerCharacter::Mouse_Y);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("Mouse_Wheel"), this, &APlayerCharacter::Mouse_Wheel);

	//Action
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Action_Jump"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_Jump);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Action_Attack"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_Attack);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Skill_1"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_Skill_1);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Evade"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_Evade);
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!IsValid(m_pAnim))
		return fDamage;

	m_pAnim->Set_AnimType(EPlayerAnimType::Hit);

	fDamage = fDamage - m_fArmorPoint;
	fDamage = fDamage > 0.f ? fDamage : 1.f;

	m_fHP -= fDamage;

	FString str = FString::Printf(TEXT("hp : %f"), m_fHP);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, str);

	AUEGameModeBase* pGameMode = Cast<AUEGameModeBase>(GetWorld()->GetAuthGameMode());

	pGameMode->Get_MainWidget()->Set_HPBar(m_fHP / m_fHPMax);

	return fDamage;
}

void APlayerCharacter::Move_Forward(float fScale)
{
	if (!IsValid(m_pAnim))
		return;

	FString strAnimType = m_pAnim->Get_AnimType();

	if (TEXT("Evade") == strAnimType)
		return;

	if (0.f == fScale || TEXT("Hit") == strAnimType)
	{
		ERunType type = m_pAnim->Get_RunType();

		if (ERunType::RunFront == type || ERunType::RunBack == type)
			m_pAnim->Set_RunType(ERunType::RunNone);

		return;
	}

	if (TEXT("Idle") == strAnimType || TEXT("Run") == strAnimType)
	{
		AddMovementInput(GetActorForwardVector(), fScale);

		ERunType type = fScale > 0.f ? ERunType::RunFront : ERunType::RunBack;

		m_pAnim->Set_RunType(type);
	}
}

void APlayerCharacter::Move_Side(float fScale)
{
	if (!IsValid(m_pAnim))
		return;

	FString strAnimType = m_pAnim->Get_AnimType();

	if (0.f == fScale || TEXT("Hit") == strAnimType || TEXT("Evade") == strAnimType)
	{
		m_pAnim->Add_Yaw(0.f);
		return;
	}

	if (TEXT("Idle") == strAnimType || TEXT("Run") == strAnimType)
	{
		AddMovementInput(GetActorRightVector(), fScale);

		ERunType curType = m_pAnim->Get_RunType();

		ERunType type = ERunType::RunNone;

		GetWorld()->GetDeltaSeconds();

		float fDirection = fScale > 0.f ? 1.f : -1.f;

		m_pAnim->Add_Yaw(fDirection);

		if (ERunType::RunFront != curType && ERunType::RunBack != curType)
		{
			type = fScale > 0.f ? ERunType::RunRight : ERunType::RunLeft;

			m_pAnim->Set_RunType(type);
		}
	}
}

void APlayerCharacter::Mouse_X(float fScale)
{
	AddControllerYawInput(fScale);
}

void APlayerCharacter::Mouse_Y(float fScale)
{
	m_pSpringArm->AddRelativeRotation(FRotator(fScale, 0.f, 0.f));
}

void APlayerCharacter::Mouse_Wheel(float fScale)
{
	m_pSpringArm->TargetArmLength -= fScale * 25.f;

	m_pSpringArm->TargetArmLength = m_pSpringArm->TargetArmLength < 100.f ? 100.f : m_pSpringArm->TargetArmLength;
}

void APlayerCharacter::Action_Jump()
{
	if (false == m_pAnim->Get_JumpEnable())
		return;

	Jump();

	m_pAnim->Set_AnimType(EPlayerAnimType::Jump);
}

void APlayerCharacter::Action_Attack()
{
	//if (false == m_isAttacking)
	//{
	//	switch (m_iAttackCombo)
	//	{
	//	case (int32)EAttackType::AttackNone:
	//		m_iAttackCombo = (int32)EAttackType::Attack1;
	//		break;
	//	case (int32)EAttackType::Attack1:
	//		m_iAttackCombo = (int32)EAttackType::Attack2;
	//		break;
	//	case (int32)EAttackType::Attack2:
	//		m_iAttackCombo = (int32)EAttackType::Attack3;
	//		break;
	//	case (int32)EAttackType::Attack3:
	//		m_iAttackCombo = (int32)EAttackType::Attack4;
	//		break;
	//	}
	//}
	//else
	//{
	//	m_isSaveAttack = true;
	//}

	//m_pAnim->Set_AnimType(EPlayerAnimType::Attack);

	//m_pAnim->Set_AttackType();
}

void APlayerCharacter::Action_Skill_1()
{
	m_pAnim->Set_AnimType(EPlayerAnimType::Skill_Q);
}

void APlayerCharacter::Action_Evade()
{
	if (TEXT("Evade") == m_pAnim->Get_AnimType())
		return;

	m_pAnim->Set_AnimType(EPlayerAnimType::Evade);

	m_isEvading = true;
}

void APlayerCharacter::Fireball()
{
	auto fireball = GetWorld()->SpawnActor<ASkillProjectile>();

	FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f + FVector(0.f, 10.f, 0.f);

	fireball->SetActorLocationAndRotation(vPos, GetActorRotation());

	UProjectileMovementComponent* pMovement = Cast<UProjectileMovementComponent>(fireball->GetComponentByClass(UProjectileMovementComponent::StaticClass()));

	if (IsValid(pMovement))
	{
		pMovement->Velocity = GetActorForwardVector() * pMovement->InitialSpeed;
	}
}

bool APlayerCharacter::CollisionCheck(TArray<FHitResult>& resultOut)
{
	FCollisionQueryParams tParams(NAME_None, false, this);

	FVector vForward = GetActorForwardVector();
	FVector vLoc = GetActorLocation() + vForward * m_fAttackRange;
	FVector vBox(m_fAttackRange, 150.f, 200.f);
	FRotator rot = GetActorRotation();


	bool bCollision = GetWorld()->SweepMultiByChannel(resultOut, vLoc, vLoc, rot.Quaternion()
		, (ECollisionChannel)CollisionPlayerAttack, FCollisionShape::MakeBox(vBox), tParams);

#if ENABLE_DRAW_DEBUG

	FVector vCenter = vLoc;

	FColor DrawColor = bCollision ? FColor::Red : FColor::Green;

	DrawDebugBox(GetWorld(), vCenter, vBox, DrawColor, false, 2.f);
#endif

	if (bCollision)
	{
		FDamageEvent tEvent;

		LOGW(TEXT("CollCnt : %d"), resultOut.Num());

		for (auto& result : resultOut)
		{
			result.GetActor()->TakeDamage(m_fAttackPoint, tEvent, GetController(), this);

			FActorSpawnParameters tSpawnParams;

			tSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			auto HitEffect = GetWorld()->SpawnActor<ASkillEffect>(result.ImpactPoint, result.ImpactNormal.Rotation(), tSpawnParams);

			HitEffect->Load_Particle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_water.P_ky_hit_water'"));
		}

	}

	return bCollision;
}

void APlayerCharacter::Evade_Move()
{
	if (false == m_isEvading)
		return;

	ERunType type = m_pAnim->Get_RunType();

	float fScale = 1500.f * GetWorld()->GetDeltaSeconds(); // 0.55초 움직이므로 절반정도 움직인다고 보면 된다.

	FVector vLoc = GetActorLocation();

	switch (type)
	{
	case ERunType::RunNone:
	case ERunType::RunFront:
		vLoc += GetActorForwardVector() * fScale;
		break;
	case ERunType::RunBack:
		vLoc -= GetActorForwardVector() * fScale;
		break;
	case ERunType::RunLeft:
		vLoc -= GetActorRightVector() * fScale;
		break;
	case ERunType::RunRight:
		vLoc += GetActorRightVector() * fScale;
		break;
	}

	SetActorLocation(vLoc);
}

void APlayerCharacter::ResetPrimaryAttack()
{
	m_iAttackCombo = 0;

	m_isAttacking = false;
	m_isSaveAttack = false;
}