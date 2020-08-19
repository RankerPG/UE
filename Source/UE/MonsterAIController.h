#pragma once

#include "info.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

UCLASS()
class UE_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonsterAIController();

public:
	//Get
	bool GetBlackboardDataAsBool(const FName& key);
	int32 GetBlackboardDataAsInt32(const FName& key);
	float GetBlackboardDataAsFloat(const FName& key);
	UObject* GetBlackboardDataAsObject(const FName& key);
	UClass* GetBlackboardDataAsClass(const FName& key);
	FVector GetBlackboardDataAsVector(const FName& key);

	//Set
	void SetBlackboardDataAsBool(const FName& key, bool data);
	void SetBlackboardDataAsInt32(const FName& key, int32 data);
	void SetBlackboardDataAsFloat(const FName& key, float data);
	void SetBlackboardDataAsObject(const FName& key, UObject* data);
	void SetBlackboardDataAsClass(const FName& key, UClass* data);
	void SetBlackboardDataAsVector(const FName& key, const FVector& data);

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void SetBlackBoardInitiallizeData(APawn* InPawn);

protected:
	UBehaviorTree* m_pBT;
	UBlackboardData* m_pBB;

public:
	static FName m_TargetKey;
	static FName m_TraceRangeKey;
	static FName m_AttackRangeKey;
	static FName m_AttackDelayKey;
	static FName m_AttackEnableKey;
};
