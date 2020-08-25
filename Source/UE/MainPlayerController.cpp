#include "MainPlayerController.h"

AMainPlayerController::AMainPlayerController()
{
	//bShowMouseCursor = true;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//FInputModeGameAndUI inputMode;
	//SetInputMode(inputMode);
}

void AMainPlayerController::SetupInputComponent()
{

}

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}