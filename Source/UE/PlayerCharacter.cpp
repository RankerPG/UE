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

	m_isSkillQMoving = false;
}

ECharacterState APlayerCharacter::Get_State()
{
	if (!IsValid(m_pAnim))
		return ECharacterState::Running;

	return m_pAnim->Get_State();
}

void APlayerCharacter::Set_Frozen(float fFrozenTime)
{
	m_pAnim->Set_Frozen(fFrozenTime);
}

void APlayerCharacter::Set_Stun(float fStunTime)
{
	m_pAnim->Set_Stun(fStunTime);
}

void APlayerCharacter::Reset_AttackInfo()
{
	m_isAttacking = false;
	m_isSaveAttack = false;
	m_iAttackCombo = 0;
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
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Skill_Q"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_Skill_Q);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Skill_E"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_Skill_E);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Skill_R"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_Skill_R);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Evade"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_Evade);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("MouseEnable"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_MouseEnable);
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!IsValid(m_pAnim))
		return fDamage;
	
	//if (TEXT("Stun") != m_pAnim->Get_AnimType())
	//{
	//	GetWorldTimerManager().SetTimer(m_StunTimer, this, &APlayerCharacter::StunEnd, 2.f, false, -1.f);

	//	m_pAnim->Set_AnimType(EPlayerAnimType::Stun);

	//	m_isStun = true;
	//}

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

	if (0.f == fScale)
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

	if (0.f == fScale || TEXT("Evade") == strAnimType)
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
	if (false == m_pAnim->Get_JumpEnable() || true == m_isStun)
		return;

	Jump();

	m_pAnim->Set_AnimType(TEXT("Jump"));
}

void APlayerCharacter::Action_Attack()
{
}

void APlayerCharacter::Action_Skill_Q()
{
	if (TEXT("SKill_Q") == m_pAnim->Get_AnimType())
		return;

	m_pAnim->Set_AnimType(TEXT("Skill_Q"));
}
void APlayerCharacter::Action_Skill_E()
{
	if (TEXT("SKill_E") == m_pAnim->Get_AnimType())
		return;

	m_pAnim->Set_AnimType(TEXT("Skill_E"));
}

void APlayerCharacter::Action_Skill_R()
{
	if (TEXT("SKill_R") == m_pAnim->Get_AnimType())
		return;

	m_pAnim->Set_AnimType(TEXT("Skill_R"));
}

void APlayerCharacter::Action_Evade()
{
	FString strType = m_pAnim->Get_AnimType();

	if (TEXT("Evade") == strType || TEXT("Skill_E") == strType || ECharacterState::Stun == m_pAnim->Get_State())
		return;

	m_pAnim->Set_AnimType(TEXT("Evade"));

	m_isEvading = true;
}

void APlayerCharacter::Action_MouseEnable()
{
	Cast<APlayerController>(GetController())->bShowMouseCursor ^= true;
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
	// 공격에 따른 범위 지정을 위해 설정.
	int iAttackType = 0;

	iAttackType = TEXT("Skill_E") == m_pAnim->Get_AnimType() ? 1 : 0;
	iAttackType = TEXT("Skill_Q") == m_pAnim->Get_AnimType() ? 2 : iAttackType;

	FCollisionQueryParams tParams(NAME_None, false, this);

	FVector vForward = GetActorForwardVector();
	FVector vLoc = GetActorLocation() ;
	FVector vBox(m_fAttackRange, 150.f, 200.f);
	FRotator rot = GetActorRotation();

	// 더 많아지면 switch로 변경
	if (1 == iAttackType) // Skill_E
	{
		vLoc += vForward * m_fAttackRange - FVector(0.f, 0.f, -100.f);
	}
	else if (2 == iAttackType) // Skill_Q
	{
		vBox = FVector(100.f, 100.f, 200.f);
		vLoc += vForward * 50.f;
	}
	else
	{
		vLoc += vForward * m_fAttackRange;
	}

	bool bCollision = GetWorld()->SweepMultiByChannel(resultOut, vLoc, vLoc, rot.Quaternion()
		, (ECollisionChannel)CollisionPlayerAttack, FCollisionShape::MakeBox(vBox), tParams);

#if ENABLE_DRAW_DEBUG

	FVector vCenter = vLoc;

	FColor DrawColor = bCollision ? FColor::Red : FColor::Green;

	DrawDebugBox(GetWorld(), vCenter, vBox, DrawColor, false, 2.f);
#endif

	if (true == bCollision)
	{
		FDamageEvent tEvent;

		LOGW("CollCnt : %d", resultOut.Num());

		for (auto& result : resultOut)
		{
			AMonster* pMonster = Cast<AMonster>(result.GetActor());

			pMonster->TakeDamage(m_fAttackPoint, tEvent, GetController(), this);

			FActorSpawnParameters tSpawnParams;

			tSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			auto HitEffect = GetWorld()->SpawnActor<ASkillEffect>(result.ImpactPoint, result.ImpactNormal.Rotation(), tSpawnParams);

			// 더 많아지면 switch로 변경
			if (1 == iAttackType) // Skill_E
			{
				HitEffect->Load_Particle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_ice.P_ky_hit_ice'"));
				pMonster->Set_Frozen(3.f);
			}
			else if (2 == iAttackType) // Skill_Q
			{
				HitEffect->Load_Particle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_water.P_ky_hit_water'"));
				pMonster->Set_Stun(3.f);
			}
			else
			{
				HitEffect->Load_Particle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_water.P_ky_hit_water'"));
			}
		}
	}

	return bCollision;
}

bool APlayerCharacter::CollisionCheck_Sphere(TArray<FHitResult>& resultOut)
{
	FCollisionQueryParams tParams(NAME_None, false, this);

	FVector vLoc = GetActorLocation();
	FRotator rot = GetActorRotation();

	bool bCollision = GetWorld()->SweepMultiByChannel(resultOut, vLoc, vLoc, rot.Quaternion()
		, (ECollisionChannel)CollisionPlayerAttack, FCollisionShape::MakeSphere(2000.f), tParams);

#if ENABLE_DRAW_DEBUG

	FVector vCenter = vLoc;

	FColor DrawColor = bCollision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), vCenter, 2000.f, 10, DrawColor, false, 1.f);
#endif

	if (true == bCollision)
	{
		FVector vForward = GetActorForwardVector();

		FDamageEvent tEvent;

		LOGW("CollCnt : %d", resultOut.Num());

		for (auto& result : resultOut)
		{
			AMonster* pMonster = Cast<AMonster>(result.GetActor());

			FVector vDir = pMonster->GetActorLocation() - vLoc;
			vDir.Normalize();

			float fAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(vForward, vDir)));

			LOGW("angle : %f", fAngle);

			if (40.f > fAngle)
			{
				pMonster->Set_Frozen(5.f);

				FActorSpawnParameters tSpawnParams;

				tSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				auto HitEffect = GetWorld()->SpawnActor<ASkillEffect>(result.ImpactPoint, result.ImpactNormal.Rotation(), tSpawnParams);

				HitEffect->Load_Particle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_ice.P_ky_hit_ice'"));

				pMonster->TakeDamage(m_fAttackPoint, tEvent, GetController(), this);
			}
		}
	}

	return bCollision;
}

bool APlayerCharacter::CollisionCheck_Knockback(TArray<FHitResult>& resultOut)
{
	FCollisionQueryParams tParams(NAME_Name, false, this);

	FVector vLoc = GetActorLocation();
	FVector vForward = GetActorForwardVector();
	FRotator rot = GetActorRotation();
	FVector vBox(100.f, 100.f, 200.f);

	bool bCollision = GetWorld()->SweepMultiByChannel(resultOut, vLoc, vLoc, rot.Quaternion()
		, (ECollisionChannel)CollisionPlayerAttack, FCollisionShape::MakeBox(vBox), tParams);

//#if ENABLE_DRAW_DEBUG
//	FVector vCenter = vLoc;
//
//	FColor color = bCollision ? FColor::Red : FColor::Green;
//
//	DrawDebugBox(GetWorld(), vCenter, vBox, color, false, 1.f);
//#endif

	if (true == bCollision)
	{
		for (auto result : resultOut)
		{
			AMonster* pMonster = Cast<AMonster>(result.GetActor());

			pMonster->Set_Knockback(0.25f);

			FVector vMonsterLoc = pMonster->GetActorLocation() + (vForward * 2000.f * GetWorld()->GetDeltaSeconds());

			pMonster->SetActorLocation(vMonsterLoc);
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

void APlayerCharacter::SkillQ_Move()
{
	if (false == m_isSkillQMoving)
		return;

	float fScale = 2000.f * GetWorld()->GetDeltaSeconds(); // 0.6초

	FVector vLoc = GetActorLocation() + GetActorForwardVector() * fScale;

	TArray<FHitResult> resultArray;

	CollisionCheck_Knockback(resultArray);

	SetActorLocation(vLoc);
}

void APlayerCharacter::ResetPrimaryAttack()
{
	m_iAttackCombo = 0;

	m_isAttacking = false;
	m_isSaveAttack = false;
}
