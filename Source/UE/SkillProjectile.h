// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "info.h"
#include "GameFramework/Actor.h"
#include "SkillProjectile.generated.h"

UCLASS()
class UE_API ASkillProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnStop(const FHitResult& tHit);

protected:
	UPROPERTY(category = Movement, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
	UProjectileMovementComponent* m_pMovement;

	UPROPERTY(category = Particle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
	UParticleSystemComponent* m_pParticle;

	UPROPERTY(category = mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
	UStaticMeshComponent* m_pMesh;

	float m_fMaxDistance;
};
