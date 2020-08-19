// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster.h"

FName AMonsterAIController::m_TargetKey(TEXT("Target"));
FName AMonsterAIController::m_TraceRangeKey(TEXT("TraceRange"));
FName AMonsterAIController::m_AttackRangeKey(TEXT("AttackRange"));
FName AMonsterAIController::m_AttackDelayKey(TEXT("AttackDelay"));
FName AMonsterAIController::m_AttackEnableKey(TEXT("AttackEnable"));

AMonsterAIController::AMonsterAIController()
{
}

bool AMonsterAIController::GetBlackboardDataAsBool(const FName& key)
{
	return Blackboard->GetValueAsBool(key);
}

int32 AMonsterAIController::GetBlackboardDataAsInt32(const FName& key)
{
	return Blackboard->GetValueAsInt(key);
}

float AMonsterAIController::GetBlackboardDataAsFloat(const FName& key)
{
	return Blackboard->GetValueAsFloat(key);
}

UObject* AMonsterAIController::GetBlackboardDataAsObject(const FName& key)
{
	return Blackboard->GetValueAsObject(key);
}

UClass* AMonsterAIController::GetBlackboardDataAsClass(const FName& key)
{
	return Blackboard->GetValueAsClass(key);
}

FVector AMonsterAIController::GetBlackboardDataAsVector(const FName& key)
{
	return Blackboard->GetValueAsVector(key);
}

void AMonsterAIController::SetBlackboardDataAsBool(const FName& key, bool data)
{
	Blackboard->SetValueAsBool(key, data);
}

void AMonsterAIController::SetBlackboardDataAsInt32(const FName& key, int32 data)
{
	Blackboard->SetValueAsInt(key, data);
}

void AMonsterAIController::SetBlackboardDataAsFloat(const FName& key, float data)
{
	Blackboard->SetValueAsFloat(key, data);
}

void AMonsterAIController::SetBlackboardDataAsObject(const FName& key, UObject* data)
{
	Blackboard->SetValueAsObject(key, data);
}

void AMonsterAIController::SetBlackboardDataAsClass(const FName& key, UClass* data)
{
	Blackboard->SetValueAsClass(key, data);
}

void AMonsterAIController::SetBlackboardDataAsVector(const FName& key, const FVector& data)
{
	Blackboard->SetValueAsVector(key, data);
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMonsterAIController::SetBlackBoardInitiallizeData(APawn* InPawn)
{
	AMonster* pMonster = Cast<AMonster>(InPawn);

	if (!pMonster)
		return;

	SetBlackboardDataAsFloat(m_TraceRangeKey, pMonster->Get_TraceRange());
	SetBlackboardDataAsFloat(m_AttackRangeKey, pMonster->Get_AttackRange());
}
