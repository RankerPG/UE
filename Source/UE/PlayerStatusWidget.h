#pragma once

#include "info.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusWidget.generated.h"

UCLASS()
class UE_API UPlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

protected:
	class UImage* m_pPlayerImage;
	class UTextBlock* m_pTextName;
	class UTextBlock* m_pTextLevel;
	class UTextBlock* m_pTextAttack;
	class UTextBlock* m_pTextArmor;
	class UTextBlock* m_pTextAttackRange;
	class UTextBlock* m_pTextHP;
	class UTextBlock* m_pTextMP;
};
