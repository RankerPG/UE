#pragma once

#include "info.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusHUDWidget.generated.h"

UCLASS()
class UE_API UPlayerStatusHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Set_HPBar(float fPercent);

	void Set_MPBar(float fPercent);

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UProgressBar* m_pHPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UProgressBar* m_pMPBar;
};
