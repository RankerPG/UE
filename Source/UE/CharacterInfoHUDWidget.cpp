#include "CharacterInfoHUDWidget.h"
#include <components/ProgressBar.h>

void UCharacterInfoHUDWidget::Set_HPBar(float fPercent)
{
	m_pHPBar->SetPercent(fPercent);
}

void UCharacterInfoHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));

	LOGW("Constructor");
}

void UCharacterInfoHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}