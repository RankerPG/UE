#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "Weapon.h"
#include "SkillProjectile.h"
#include "DrawDebugHelpers.h"
#include "Monster.h"
#include "SkillEffect.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("SkeletalMesh'/Game/Player/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi.Shinbi'"));

	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	m_pMesh = GetMesh();

	ConstructorHelpers::FClassFinder<UPlayerAnimInstance> ClassFinder(TEXT("AnimBlueprint'/Game/Player/BP_Anim.BP_Anim_C'"));

	if (ClassFinder.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ClassFinder.Class);
	}

	m_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_pSpringArm->SetupAttachment(RootComponent);

	m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_pCamera->SetupAttachment(m_pSpringArm);


	m_pSpringArm->TargetArmLength = 700.f;
	m_pSpringArm->TargetOffset.Z = 70.f;
	m_pSpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	m_pSpringArm->bDoCollisionTest = false;

	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;

	//
	m_pWeapon = nullptr;

	ConstructorHelpers::FClassFinder<AWeapon> WeaponClass(TEXT("Blueprint'/Game/Item/BP_Weapon.BP_Weapon_C'"));

	if (WeaponClass.Succeeded())
	{
		m_pWeaponClass = WeaponClass.Class;
	}

	m_fAttackRange = 250.f; //half

	m_fAttackPoint = 20.f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_pAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	m_pWeapon = GetWorld()->SpawnActor<AWeapon>(m_pWeaponClass);

	m_pWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_l"));

	m_pWeapon->Load_Weapon(TEXT("StaticMesh'/Game/Item/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Sword.SM_Sword'"));
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
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Drop_Weapon"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_DropWeapon);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Skill_1"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_Skill_1);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Dash"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Action_Dash);
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!IsValid(m_pAnim))
		return fDamage;

	m_pAnim->Set_AnimType(EPlayerAnimType::Hit);

	return fDamage;
}

void APlayerCharacter::Move_Forward(float fScale)
{
	if (!IsValid(m_pAnim))
		return;

	FString strAnimType = m_pAnim->Get_AnimType();

	if (TEXT("Dash") == strAnimType)
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

	if (0.f == fScale || TEXT("Hit") == strAnimType || TEXT("Dash") == strAnimType)
		return;

	if (TEXT("Idle") == strAnimType || TEXT("Run") == strAnimType)
	{
		AddMovementInput(GetActorRightVector(), fScale);

		ERunType curType = m_pAnim->Get_RunType();

		ERunType type = ERunType::RunNone;

		if (ERunType::RunFront == curType)
		{
			type = fScale > 0.f ? ERunType::RunFrontRight : ERunType::RunFrontLeft;

			m_pAnim->Set_RunType(type);
		}
		else if (ERunType::RunBack == curType)
		{
			type = fScale > 0.f ? ERunType::RunBackRight : ERunType::RunBackLeft;

			m_pAnim->Set_RunType(type);
		}
		else
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
	if (TEXT("Jump") == m_pAnim->Get_AnimType())
		return;

	Jump();

	m_pAnim->Set_AnimType(EPlayerAnimType::Jump);
}

void APlayerCharacter::Action_Attack()
{
	m_pAnim->Set_AnimType(EPlayerAnimType::Attack);

	m_pAnim->Set_AttackType();
}

void APlayerCharacter::Action_DropWeapon()
{
	if (IsValid(m_pWeapon))
	{
		m_pWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		m_pWeapon->Drop();

		m_pWeapon = nullptr;
	}
}

void APlayerCharacter::Action_Skill_1()
{
	m_pAnim->Set_AnimType(EPlayerAnimType::Skill);
}

void APlayerCharacter::Action_Dash()
{
	if (TEXT("Dash") == m_pAnim->Get_AnimType())
		return;

	m_pAnim->Set_AnimType(EPlayerAnimType::Dash);
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

void APlayerCharacter::Move_Dash()
{
	FVector vLoc = GetActorLocation();

	ERunType type = m_pAnim->Get_RunType();

	FVector vDashDir;

	FRotator rot = m_pMesh->GetRelativeRotation();

	LOGW(TEXT("type : %d"), type);

	switch (type)
	{
	case ERunType::RunNone:
	case ERunType::RunFront:
	case ERunType::RunFrontLeft:
	case ERunType::RunFrontRight:
		vDashDir = GetActorForwardVector();
		m_rotDash = FRotator::ZeroRotator;
		break;
	case ERunType::RunBack:
	case ERunType::RunBackLeft:
	case ERunType::RunBackRight:
		vDashDir = -GetActorForwardVector();
		rot += m_rotDash = FRotator(0.f, -180.f, 0.f);
		m_pMesh->SetRelativeRotation(rot);
		break;
	case ERunType::RunLeft:
		vDashDir = -GetActorRightVector();
		rot += FRotator(0.f, -90.f, 0.f);
		m_rotDash = FRotator(0.f, 90.f, 0.f);
		m_pMesh->SetRelativeRotation(rot);
		break;
	case ERunType::RunRight:
		vDashDir = GetActorRightVector();
		rot += FRotator(0.f, 90.f, 0.f);
		m_rotDash = FRotator(0.f, -90.f, 0.f);
		m_pMesh->SetRelativeRotation(rot);
		break;
	}

	vLoc += vDashDir * 1500.f;

	SetActorLocation(vLoc);
}

void APlayerCharacter::Dash_End()
{
	FRotator rot = m_pMesh->GetRelativeRotation() + m_rotDash;

	m_pMesh->SetRelativeRotation(rot);

	rot = FRotator::ZeroRotator;
}