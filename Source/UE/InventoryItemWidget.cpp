#include "InventoryItemWidget.h"
#include <components/Image.h>
#include <components/TextBlock.h>
#include "InventoryItemData.h"

void UInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pIconImage = Cast<UImage>(GetWidgetFromName(TEXT("Image_Icon")));

	m_pTextName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name")));

	m_pTextCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Count")));
}

void UInventoryItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryItemWidget::Set_Data(class UInventoryItemData* pData)
{
	m_iCount = pData->Get_ItemCount();

	FString strCount = FString::Printf(TEXT("%d"), m_iCount);

	m_pTextCount->SetText(FText::FromString(strCount));

	m_pTextName->SetText(FText::FromString(pData->Get_ItemName()));

	m_pIconImage->SetBrushFromTexture(pData->Get_ItemIconTexture());
}