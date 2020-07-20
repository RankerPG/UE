#pragma once

#include "info.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveTarget.generated.h"

UCLASS()
class UE_API UBTTask_MoveTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

protected:
	UPROPERTY(category = Node, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fRange;
};
