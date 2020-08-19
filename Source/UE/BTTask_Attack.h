// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "info.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"


UCLASS()
class UE_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Attack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	void AttackEnd();

private:
	bool m_bAttack;
};
