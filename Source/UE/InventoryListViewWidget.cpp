#include "InventoryListViewWidget.h"
#include <Components/ListView.h>
#include "InventoryItemData.h"
#include "PlayerCharacter.h"

void UInventoryListViewWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Collapsed);

	//m_pPlayer = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void UInventoryListViewWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryListViewWidget::InitList()
{
	// 생성자보다 먼저 호출되서 옮김
	m_pListView = Cast<UListView>(GetWidgetFromName(TEXT("InventoryListView")));

	for (int i = 0; i < 20; ++i)
	{
		UInventoryItemData* pData = NewObject<UInventoryItemData>(this, UInventoryItemData::StaticClass());

		pData->Set_ItemIndex(i);
		pData->Set_ItemCount(i + 1);
		pData->Set_ItemName(TEXT("Weapon"));
		pData->Set_ItemIconTexture(TEXT("Texture2D'/Game/UI/weapon.weapon'"));
		
		m_pListView->AddItem(pData);
	}
}

void UInventoryListViewWidget::UseItem(UInventoryItemData* pData)
{
	//m_pPlayer->Update_HP(20.f);
}