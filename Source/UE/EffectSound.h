#pragma once

#include "info.h"
#include "GameFramework/Actor.h"
#include "EffectSound.generated.h"

UCLASS()
class UE_API AEffectSound : public AActor
{
	GENERATED_BODY()
	
public:
	AEffectSound();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void SetAudio(USoundBase* pSoundBase);
	void SetVolume(float fVolume);
	void LoadAudio(const FString& strPath);
	void Play();
	void Stop();

	UFUNCTION()
	void EndAudio();

private:
	UPROPERTY(category = sound, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* m_pAudio;

};
