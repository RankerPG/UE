#include "BTTask_Attack.h"
#include "MonsterAIController.h"
#include "Monster.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!pController)
	{
		return EBTNodeResult::Failed;
	}

	AMonster* pMonster = pController->GetPawn<AMonster>();

	if (!pMonster)
	{
		return EBTNodeResult::Failed;
	}

	pMonster->Add_AttackEndFunction<UBTTask_Attack>(this, &UBTTask_Attack::AttackEnd);

	m_bAttack = true;

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!pController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	AMonster* pMonster = pController->GetPawn<AMonster>();

	if (!pMonster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (0.f < pMonster->Get_HP() && TEXT("Hit") != pMonster->Get_AnimType() && ECharacterState::Frozen != pMonster->Get_State())
	{
		pMonster->Set_AnimSequence(TEXT("Attack"));
	}

	AActor* pTarget = Cast<AActor>(pController->GetBlackboardDataAsObject(AMonsterAIController::m_TargetKey));

	if (IsValid(pTarget))
	{
		FVector vDir = pTarget->GetActorLocation() - pMonster->GetActorLocation();
		vDir.Normalize();

		pMonster->SetActorRotation(vDir.Rotation());
	}

	if (!m_bAttack)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_Attack::AttackEnd()
{
	m_bAttack = false;
}