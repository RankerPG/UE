#pragma once

#include "info.h"
#include "Blueprint/UserWidget.h"
#include "DamageFontWidget.generated.h"

UCLASS()
class UE_API UDamageFontWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Set_Onwer(class UWidgetComponent* pOwner);
	void Set_DamageText(FString strDamage);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void UnVisible();

private:
	UPROPERTY(category = text, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* m_pTextDamage;

	FTimerHandle m_VisibleTimerHander;

	class UWidgetComponent* m_pOwner;

	FVector m_vOwnerPos;

	bool m_isAnimation;
};
