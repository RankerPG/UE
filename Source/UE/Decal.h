#pragma once

#include "info.h"
#include "GameFramework/Actor.h"
#include "Decal.generated.h"

UCLASS()
class UE_API ADecal : public AActor
{
	GENERATED_BODY()
	
public:	
	ADecal();

public:
	void Set_DecalSize(FVector vSize) { m_pDecal->DecalSize = vSize; }
	void Set_FadeTime(float fInDelay, float fInDuration, float fOutDelay, float fOutDuration);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
		void SetDecalMaterial(const FString& strPath);

private:
	UPROPERTY(category = Decal, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UDecalComponent* m_pDecal;
};
