#pragma once

#include "Info.h"
#include "Monster.h"
#include "Minion.generated.h"

UCLASS()
class UE_API AMinion : public AMonster
{
	GENERATED_BODY()
	
public:
	AMinion();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

public:
	void Shot_Bullet();

private:
	UClass* m_BulletClass;

	USkeletalMeshComponent* m_pMesh;
};
