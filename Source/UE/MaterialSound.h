#pragma once

#include "info.h"
#include "UObject/NoExportTypes.h"
#include "MaterialSound.generated.h"

UCLASS()
class UE_API UMaterialSound : public UObject
{
	GENERATED_BODY()
	
public:
	UMaterialSound();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllocPrivateAccess = "true"))
		TMap<FString, USoundBase*> m_SoundMap;

public:
	bool Load_Sound(const FString& strName, const FString& strPath);
	USoundBase* Find_Sound(const FString& strName);
};
