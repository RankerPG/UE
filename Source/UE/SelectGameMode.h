#pragma once

#include "info.h"
#include "GameFramework/GameModeBase.h"
#include "SelectGameMode.generated.h"

UCLASS()
class UE_API ASelectGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASelectGameMode();

protected:
	virtual void BeginPlay();

private:
	TSubclassOf<UUserWidget> m_ChracterDescWidgetClass;
	class UCharacterDescWidget* m_pDescWidget;
};
