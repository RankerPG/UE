#pragma once

#include "info.h"
#include "GameFramework/Actor.h"
#include "SkillEffect.generated.h"

UCLASS()
class UE_API ASkillEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	ASkillEffect();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Load_Particle(const FString& strPath);

	UFUNCTION()
	void OnFinished(UParticleSystemComponent* pSystem);

protected:
	UPROPERTY(category = Particle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
	UParticleSystemComponent* m_pParticle;
};
