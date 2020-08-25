#include "BTTask_MoveTarget.h"
#include "MonsterAIController.h"
#include "Monster.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem/Public/NavigationPath.h"

UBTTask_MoveTarget::UBTTask_MoveTarget()
{
	NodeName = TEXT("MoveToTarget");
	bNotifyTick = true;
	m_fRange = 10.f;
}

EBTNodeResult::Type UBTTask_MoveTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!pController)
		return EBTNodeResult::Failed;

	AActor* pTarget = Cast<AActor>(pController->GetBlackboardDataAsObject(AMonsterAIController::m_TargetKey));

	if (!pTarget)
		return EBTNodeResult::Failed;

	m_fRange = pController->GetBlackboardDataAsFloat(AMonsterAIController::m_AttackRangeKey);

	return EBTNodeResult::InProgress;
}

void UBTTask_MoveTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	AMonster* pMonster = pController->GetPawn<AMonster>();

	ACharacter* pTarget = Cast<ACharacter>(pController->GetBlackboardDataAsObject(AMonsterAIController::m_TargetKey));

	if (!pTarget)
	{
		pController->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	if (!pMonster)
		return;

	if (pMonster->Get_HP() > 0.f && ECharacterState::Frozen != pMonster->Get_State())
	{
		pMonster->Set_AnimSequence(TEXT("Run"));

		pMonster->GetCharacterMovement()->MaxWalkSpeed = 600.f;

		UAIBlueprintHelperLibrary::SimpleMoveToActor(pController, pTarget);
	}

	FVector vMonsterPos = pMonster->GetMesh()->GetComponentLocation();
	FVector vTargetPos = pTarget->GetMesh()->GetComponentLocation();

	float fDist = FVector::Distance(vMonsterPos, vTargetPos);

	if (fDist < m_fRange)
	{
		pController->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}
}
