// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "info.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class UE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Drop();

	void Load_Weapon(const FString& strPath);

protected:
	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_pMesh;

};
