// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "info.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_InAttackRange.generated.h"

UCLASS()
class UE_API UBTDecorator_InAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_InAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
