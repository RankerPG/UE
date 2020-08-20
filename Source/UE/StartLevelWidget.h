#pragma once

#include "info.h"
#include "Blueprint/UserWidget.h"
#include "StartLevelWidget.generated.h"

UCLASS()
class UE_API UStartLevelWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
		void Click_StartButton();

	UFUNCTION()
		void Click_EndButton();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* m_pStartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* m_pEndButton;
};
