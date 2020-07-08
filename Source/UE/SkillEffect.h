// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "info.h"
#include "GameFramework/Actor.h"
#include "SkillEffect.generated.h"

UCLASS()
class UE_API ASkillEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Load_Particle(const FString& strPath);

	UFUNCTION()
	void OnFinished(UParticleSystemComponent* pSystem);

protected:
	UPROPERTY(category = Particle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
	UParticleSystemComponent* m_pParticle;
};
