// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillProjectile.h"
#include "SkillEffect.h"


// Sets default values
ASkillProjectile::ASkillProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	m_pParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	m_pMovement->InitialSpeed = m_pMovement->MaxSpeed = 1500.f;
	m_pMovement->ProjectileGravityScale = 0.f;


	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleFinder(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_shot_fire.P_ky_shot_fire'"));

	if (ParticleFinder.Succeeded())
	{
		m_pParticle->SetTemplate(ParticleFinder.Object);
	}

	m_pParticle->AttachToComponent(m_pMesh, FAttachmentTransformRules::KeepRelativeTransform);

	m_pParticle->SetWorldScale3D(FVector(2.f, 2.f, 2.f));
	m_pParticle->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("StaticMesh'/Game/MS_ForestTut/3D_Asset/01_Granite_Rock_pkeeM/Aset_rock_granite_M_pkeeM_LOD0.Aset_rock_granite_M_pkeeM_LOD0'"));

	if (MeshFinder.Succeeded())
	{
		m_pMesh->SetStaticMesh(MeshFinder.Object);
	}

	RootComponent = m_pMesh;

	m_fMaxDistance = 1000.f;
}

// Called when the game starts or when spawned
void ASkillProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));

	m_pMovement->OnProjectileStop.AddDynamic(this, &ASkillProjectile::OnStop);
}

// Called every frame
void ASkillProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float fSpeed = m_pMovement->InitialSpeed * DeltaTime;

	if (0.f == fSpeed)
		fSpeed = m_pMovement->Velocity.Size();

	m_fMaxDistance -= fSpeed;

	if (m_fMaxDistance <= 0.f)
	{
		Destroy();
	}
}

void ASkillProjectile::OnStop(const FHitResult& tHit)
{
	auto hitEffect = GetWorld()->SpawnActor<ASkillEffect>();

	hitEffect->Load_Particle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_fire.P_ky_hit_fire'"));

	hitEffect->SetActorLocationAndRotation(tHit.ImpactPoint, GetActorRotation());

	Destroy();
}
