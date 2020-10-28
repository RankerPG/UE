#pragma once

#include "info.h"
#include "GameFramework/Actor.h"
#include "IceSpike.generated.h"

UCLASS()
class UE_API AIceSpike : public AActor
{
	GENERATED_BODY()
	
public:	
	AIceSpike();

public:
	void Set_ArrayAndIndex(TArray<AIceSpike*>* pArray, int iIndex);
	void Set_VisibleTime(float fTime);
	void Set_SoundPlayActor(bool isSoundPlay) { m_isSoundPlayActor = isSoundPlay; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void Visible_IceSpike();
	void Destroy_IceSpike();
	void Setup_Location();
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(category = Mesh, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_pMesh;

	UPROPERTY(category = Capsule, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_pCapsule;

	TArray<AIceSpike*>* m_pArray;
	int m_iIndex;

	FTimerHandle VisibleTimerHandle;
	FTimerHandle DestroyTimerHandle;

	float m_fVisibleTime;
	float m_fDestroyTime;

	bool m_isSoundPlayActor;
};
