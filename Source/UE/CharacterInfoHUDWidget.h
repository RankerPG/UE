#pragma once

#include "info.h"
#include "Blueprint/UserWidget.h"
#include "CharacterInfoHUDWidget.generated.h"

UCLASS()
class UE_API UCharacterInfoHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Set_HPBar(float fPercent);

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UProgressBar* m_pHPBar;
};
