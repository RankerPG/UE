#include "IceSpike.h"
#include "SkillEffect.h"
#include "EffectSound.h"

AIceSpike::AIceSpike()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	m_pCapsule->SetCollisionProfileName(TEXT("PlayerSkill"));
	RootComponent = m_pCapsule;

	//
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("StaticMesh'/Game/ParagonAurora/FX/Meshes/Ice/SM_Ice_Spikes.SM_Ice_Spikes'"));

	if (MeshFinder.Succeeded())
	{
		m_pMesh->SetStaticMesh(MeshFinder.Object);
	}

	m_fVisibleTime = 0.f;
	m_fDestroyTime = 5.f;

	m_pMesh->SetupAttachment(m_pCapsule);
	m_pMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_isSoundPlayActor = false;
}

void AIceSpike::Set_VisibleTime(float fTime)
{
	GetWorld()->GetTimerManager().SetTimer(VisibleTimerHandle, this, &AIceSpike::Visible_IceSpike, fTime, false);

	Setup_Location();
}

void AIceSpike::BeginPlay()
{
	Super::BeginPlay();

	m_pMesh->SetVisibility(false);
}

void AIceSpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIceSpike::Visible_IceSpike()
{
	m_pMesh->SetVisibility(true);

	GetWorld()->GetTimerManager().SetTimer(VisibleTimerHandle, this, &AIceSpike::Destroy_IceSpike, m_fDestroyTime, false);

	ASkillEffect* pEffect = GetWorld()->SpawnActor<ASkillEffect>();

	pEffect->SetActorLocation(GetActorLocation());

	pEffect->Load_Particle(TEXT("ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Leap/FX/P_Aurora_Decoy_Explode_Fragments.P_Aurora_Decoy_Explode_Fragments'"));
}

void AIceSpike::Destroy_IceSpike()
{
	ASkillEffect* pEffect = GetWorld()->SpawnActor<ASkillEffect>();

	pEffect->SetActorLocation(GetActorLocation());

	pEffect->Load_Particle(TEXT("ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Leap/FX/P_Aurora_Decoy_Crumble_Fall.P_Aurora_Decoy_Crumble_Fall'"));

	// Sound
	if (true == m_isSoundPlayActor)
	{
		FActorSpawnParameters tSpawnParams;

		tSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AEffectSound* pSound = GetWorld()->SpawnActor<AEffectSound>(GetActorLocation(), GetActorRotation(), tSpawnParams);

		pSound->LoadAudio(TEXT("SoundWave'/Game/Sound/Destroy_SkillE.Destroy_SkillE'"));

		pSound->Play();
	}

	GetWorld()->DestroyActor(this);
}

void AIceSpike::Setup_Location()
{
	TArray<AActor*> ignoreActor;

	FVector vStart = GetActorLocation() - FVector::UpVector * 1000.f;

	FVector vEnd = vStart + FVector::UpVector * 2000.f;

	FHitResult result;

	bool isResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(), vStart, vEnd, UEngineTypes::ConvertToTraceType(ECC_WorldStatic), false,
		ignoreActor, EDrawDebugTrace::None, result, true);

	if (true == isResult)
	{
		FVector hitLoc = result.ImpactPoint;

		SetActorLocation(hitLoc);
	}
}