#pragma once

#include "info.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItemData.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UE_API UInventoryItemData : public UObject
{
	GENERATED_BODY()
	
public:
	//Get
	int32 Get_ItemIndex() const { return m_iIndex; }
	int32 Get_ItemCount() const { return m_iCount; }
	FString Get_ItemName() const { return m_strName; }
	UTexture2D* Get_ItemIconTexture() const { return m_pTextureIcon; }

	//Set
	void Set_ItemIndex(int32 index) { m_iIndex = index; }
	void Set_ItemCount(int32 count) { m_iCount = count; }
	void Set_ItemName(const FString& strName) { m_strName = strName; }
	void Set_ItemIconTexture(const FString& strPath) { m_pTextureIcon = LoadObject<UTexture2D>(nullptr, *strPath); }
	void Set_ItemIconTexture(UTexture2D* pTexture) { m_pTextureIcon = pTexture; }

private:
	UPROPERTY(category = Data, BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		int32 m_iIndex;

	UPROPERTY(category = Data, BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		int32 m_iCount;

	UPROPERTY(category = Data, BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		FString m_strName;

	UPROPERTY(category = Data, BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		UTexture2D* m_pTextureIcon;
};
