#include "PlayerStatusHUDWidget.h"
#include <components/ProgressBar.h>

void UPlayerStatusHUDWidget::Set_HPBar(float fPercent)
{
	m_pHPBar->SetPercent(fPercent);
}

void UPlayerStatusHUDWidget::Set_MPBar(float fPercent)
{
	m_pMPBar->SetPercent(fPercent);
}

void UPlayerStatusHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));

	if(IsValid(m_pHPBar))
		m_pHPBar->SetPercent(1.f);

	m_pMPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));

	if (IsValid(m_pMPBar))
		m_pMPBar->SetPercent(1.f);
}

void UPlayerStatusHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}