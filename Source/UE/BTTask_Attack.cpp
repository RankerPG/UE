#include "BTTask_Attack.h"
#include "MonsterAIController.h"
#include "Monster.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type	eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!pController)
		return EBTNodeResult::Failed;

	AMonster* pMonster = pController->GetPawn<AMonster>();

	if (!pMonster)
		return EBTNodeResult::Failed;

	if (0.f < pMonster->Get_HP())
	{
		pMonster->Set_AnimSequence(TEXT("Attack"));
	}

	return eResult;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
