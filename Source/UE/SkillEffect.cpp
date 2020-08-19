// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillEffect.h"

// Sets default values
ASkillEffect::ASkillEffect()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	RootComponent = m_pParticle;
}

// Called when the game starts or when spawned
void ASkillEffect::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_pParticle))
	{
		m_pParticle->OnSystemFinished.AddDynamic(this, &ASkillEffect::OnFinished);
	}
}

// Called every frame
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
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Particle Finished"));

	Destroy();
}