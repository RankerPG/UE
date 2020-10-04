#pragma once

#include "info.h"
#include "Blueprint/UserWidget.h"
#include "InventoryListViewWidget.generated.h"

UCLASS()
class UE_API UInventoryListViewWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION(BlueprintCallable)
		void InitList();

	UFUNCTION(BlueprintCallable)
		void UseItem(class UInventoryItemData* pData);

protected:
	UPROPERTY(category = Widget, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UListView* m_pListView;

	class APlayerCharacter* m_pPlayer;
};
