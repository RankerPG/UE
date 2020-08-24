#include "MainWidget.h"
#include "PlayerStatusHUDWidget.h"

void UMainWidget::Set_HPBar(float fPercent)
{
	m_pStatusHUDWidget->Set_HPBar(fPercent);
}

void UMainWidget::Set_MPBar(float fPercent)
{
	m_pStatusHUDWidget->Set_MPBar(fPercent);
}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pStatusHUDWidget = Cast<UPlayerStatusHUDWidget>(GetWidgetFromName(TEXT("StatusHUD")));
}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}