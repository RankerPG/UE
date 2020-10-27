#pragma once

#include "info.h"
#include "Monster.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class UE_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnPoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void CreateMonster();

	UFUNCTION(BluePrintCallable)
	void SpawnMonster();
	
	void CallSpawnTimer();

private:
	UPROPERTY(category = Spawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMonster> m_MonsterClass;

	UPROPERTY(category = Spawn, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<class APoint*> m_PointArray;

	class AMonster* m_pMonster;

	FTimerHandle m_TimerHandler;

	float m_fSpawnTime;
};
