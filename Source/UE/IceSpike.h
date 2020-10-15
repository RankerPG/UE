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
	void Set_VisibleTime(float fTime);
	void Set_SoundPlayActor(bool isSoundPlay) { m_isSoundPlayActor = isSoundPlay; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void Visible_IceSpike();
	void Destroy_IceSpike();

private:
	UPROPERTY(category = Mesh, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_pMesh;

	UPROPERTY(category = Capsule, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_pCapsule;

	FTimerHandle VisibleTimerHandle;
	FTimerHandle DestroyTimerHandle;

	float m_fVisibleTime;
	float m_fDestroyTime;

	bool m_isSoundPlayActor;
};
