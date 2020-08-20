#pragma once

#include "info.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameMode.generated.h"

UCLASS()
class UE_API AStartGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AStartGameMode();

private:
	TSubclassOf<UUserWidget> m_StartLevelWidgetClass;
	class UStartLevelWidget* m_pStartLevelWidget;

public:
	virtual void BeginPlay();
};
