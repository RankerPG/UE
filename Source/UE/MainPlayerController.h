#pragma once

#include "info.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

UCLASS()
class UE_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainPlayerController();

public:
	virtual void BeginPlay();
	virtual void SetupInputComponent();
	virtual void PlayerTick(float DeltaTime);
};
