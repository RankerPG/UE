#pragma once

#include "info.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

UCLASS()
class UE_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Set_HPBar(float fPercent);
	void Set_MPBar(float fPercent);

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
		void Click_StatusButton();

protected:
	class UPlayerStatusHUDWidget* m_pStatusHUDWidget;

	class UPlayerStatusWidget* m_pStatusWidget;

	class UButton* m_pStatusButton;
};
