#include "BTTask_Patrol.h"
#include "Monster.h"
#include "MonsterAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem/Public/NavigationPath.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!pController)
		return EBTNodeResult::Failed;

	AMonster* pMonster = pController->GetPawn<AMonster>();

	if (!pMonster)
		return EBTNodeResult::Failed;

	if (!pMonster->Get_PatrolEnable())
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!pController)
		return;

	ACharacter* pTarget = Cast<ACharacter>(pController->GetBlackboardDataAsObject(AMonsterAIController::m_TargetKey));

	if (pTarget)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}

	AMonster* pMonster = pController->GetPawn<AMonster>();

	if (!pMonster)
		return;

	FVector vPatrolPos = pMonster->Get_PatrolPos();

	if (pMonster->Get_HP() > 0.f)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(pController, vPatrolPos);
	}

	FVector vPos = pMonster->GetMesh()->GetComponentLocation();

	float fDist = FVector::Distance(vPos, vPatrolPos);

	if (fDist <= 50.f)
	{
		pController->StopMovement();

		pMonster->NextPatrolPos();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}