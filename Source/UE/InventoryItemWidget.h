#pragma once

#include "info.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

UCLASS()
class UE_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
		void Set_Data(class UInventoryItemData* pData);

private:
	UPROPERTY(category = info, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* m_pIconImage;

	UPROPERTY(category = widget, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* m_pTextName;

	UPROPERTY(category = widget, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* m_pTextCount;

	int m_iCount;
};
