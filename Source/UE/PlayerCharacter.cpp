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

	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;

	//
	m_pWeapon = nullptr;

	ConstructorHelpers::FClassFinder<AWeapon> WeaponClass(TEXT("Blueprint'/Game/Item/BP_Weapon.BP_Weapon_C'"));

	if (WeaponClass.Succeeded())
	{
		m_pWeaponClass = WeaponClass.Class;
	}

	m_fAttackRange = 500.f;

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

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("Move_Forward"), this, &APlayerCharacter::Move_Foward);
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
		, &APlayerCharacter::Drop_Weapon);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Skill_1"), EInputEvent::IE_Pressed, this
		, &APlayerCharacter::Skill_1);

}

void APlayerCharacter::Move_Foward(float fScale)
{
	AddMovementInput(GetActorForwardVector(), fScale);
}

void APlayerCharacter::Move_Side(float fScale)
{
	AddMovementInput(GetActorRightVector(), fScale);
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
	Jump();

	m_pAnim->Set_AnimType(EPlayerAnimType::Jump);
}

void APlayerCharacter::Action_Attack()
{
	m_pAnim->Set_AnimType(EPlayerAnimType::Attack);

	m_pAnim->Set_AttackType();
}

void APlayerCharacter::Drop_Weapon()
{
	if (IsValid(m_pWeapon))
	{
		m_pWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		m_pWeapon->Drop();

		m_pWeapon = nullptr;
	}
}

void APlayerCharacter::Skill_1()
{
	m_pAnim->Set_AnimType(EPlayerAnimType::Skill);
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

bool APlayerCharacter::CollisionCheck(FHitResult& resultOut)
{
	FCollisionQueryParams tParams(NAME_None, false, this);

	bool bCollision = GetWorld()->SweepSingleByChannel(resultOut, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * m_fAttackRange, FQuat::Identity
		, (ECollisionChannel)CollisionPlayerAttack, FCollisionShape::MakeSphere(30.f), tParams);

#if ENABLE_DRAW_DEBUG

	FVector vCenter = GetActorLocation() + GetActorForwardVector() * (m_fAttackRange / 2.f);

	FColor DrawColor = bCollision ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), vCenter, m_fAttackRange / 2.f, 30.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 2.f);
#endif

	if (bCollision)
	{
		FDamageEvent tEvent;

		resultOut.GetActor()->TakeDamage(m_fAttackPoint, tEvent, GetController(), this);

		FActorSpawnParameters tSpawnParams;

		tSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		auto HitEffect = GetWorld()->SpawnActor<ASkillEffect>(resultOut.ImpactPoint, resultOut.ImpactNormal.Rotation(), tSpawnParams);

		HitEffect->Load_Particle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_water.P_ky_hit_water'"));
	}

	return bCollision;
}