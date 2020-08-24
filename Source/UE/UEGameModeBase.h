#pragma once

#include "info.h"
#include "GameFramework/GameModeBase.h"
#include "UEGameModeBase.generated.h"

UCLASS()
class UE_API AUEGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AUEGameModeBase();

public:
	class UMainWidget* Get_MainWidget() { return m_pMainWidget; }

protected:
	virtual void BeginPlay();

private:
	TSubclassOf<UUserWidget> m_MainWidgetClass;
	class UMainWidget* m_pMainWidget;
};
