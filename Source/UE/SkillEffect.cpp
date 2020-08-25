#include "SkillEffect.h"

ASkillEffect::ASkillEffect()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	RootComponent = m_pParticle;
}

void ASkillEffect::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_pParticle))
	{
		m_pParticle->OnSystemFinished.AddDynamic(this, &ASkillEffect::OnFinished);
	}
}

void ASkillEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkillEffect::Load_Particle(const FString& strPath)
{
	UParticleSystem* pParticle = LoadObject<UParticleSystem>(nullptr, *strPath, nullptr, LOAD_None);

	if (IsValid(pParticle))
	{
		m_pParticle->SetTemplate(pParticle);
	}
}

void ASkillEffect::OnFinished(UParticleSystemComponent* pSystem)
{
	Destroy();
}