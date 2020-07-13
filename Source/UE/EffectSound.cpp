#include "EffectSound.h"

AEffectSound::AEffectSound()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	RootComponent = m_pAudio;

	m_pAudio->OnAudioFinished.AddDynamic(this, &AEffectSound::EndAudio);
}

void AEffectSound::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEffectSound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffectSound::LoadAudio(const FString& strPath)
{
	USoundWave* pSound = LoadObject<USoundWave>(nullptr, *strPath);

	if (IsValid(pSound))
	{
		m_pAudio->SetSound(pSound);
	}
}

void AEffectSound::Play()
{
	m_pAudio->Play();
}

void AEffectSound::Stop()
{
	m_pAudio->Stop();
}

void AEffectSound::EndAudio()
{
	Destroy();
}

