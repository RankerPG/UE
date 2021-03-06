// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "info.h"
#include "GameFramework/Actor.h"
#include "Point.generated.h"

UCLASS()
class UE_API APoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
