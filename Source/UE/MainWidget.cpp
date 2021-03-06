#include "MainWidget.h"
#include "PlayerStatusHUDWidget.h"
#include "PlayerStatusWidget.h"
#include "components/Button.h"
#include "inventoryListviewWidget.h"

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

	m_pStatusWidget = Cast<UPlayerStatusWidget>(GetWidgetFromName(TEXT("PlayerStatus")));

	m_pInvenWidget = Cast<UInventoryListViewWidget>(GetWidgetFromName(TEXT("InventoryListView")));

	m_pStatusButton = Cast<UButton>(GetWidgetFromName(TEXT("Button_Status")));
	m_pStatusButton->OnClicked.AddDynamic(this, &UMainWidget::Click_StatusButton);

	m_pInvenButton = Cast<UButton>(GetWidgetFromName(TEXT("Button_Inven")));
	m_pInvenButton->OnClicked.AddDynamic(this, &UMainWidget::Click_InvenButton);
}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMainWidget::Click_StatusButton()
{
	if(ESlateVisibility::Visible == m_pStatusWidget->GetVisibility())
		m_pStatusWidget->SetVisibility(ESlateVisibility::Collapsed);
	else
		m_pStatusWidget->SetVisibility(ESlateVisibility::Visible);
}

void UMainWidget::Click_InvenButton()
{
	if (ESlateVisibility::Visible == m_pInvenWidget->GetVisibility())
		m_pInvenWidget->SetVisibility(ESlateVisibility::Collapsed);
	else
		m_pInvenWidget->SetVisibility(ESlateVisibility::Visible);
}