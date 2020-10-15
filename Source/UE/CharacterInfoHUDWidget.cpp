#include "CharacterInfoHUDWidget.h"
#include <components/ProgressBar.h>
#include <components/TextBlock.h>

void UCharacterInfoHUDWidget::Set_Name(FString strName)
{
	m_strName = strName;
}

void UCharacterInfoHUDWidget::Set_HPBar(float fPercent)
{
	m_pHPBar->SetPercent(fPercent);
}

void UCharacterInfoHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));

	m_pTextName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name")));

	m_pTextName->SetText(FText::FromString(m_strName));
}

void UCharacterInfoHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}