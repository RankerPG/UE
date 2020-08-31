#include "BTTask_Attack.h"
#include "MonsterAIController.h"
#include "Monster.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;

	m_isAttackEnd = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!pController)
		return EBTNodeResult::Failed;

	AMonster* pMonster = pController->GetPawn<AMonster>();

	if (!pMonster)
		return EBTNodeResult::Failed;

	if (true == pMonster->Get_AttackEnable())
		pMonster->Set_AttackEnable(false);
	else
	{
		AActor* pTarget = Cast<AActor>(pController->GetBlackboardDataAsObject(AMonsterAIController::m_TargetKey));

		if (IsValid(pTarget))
		{
			FVector vDir = pTarget->GetActorLocation() - pMonster->GetActorLocation();

			vDir.Z = 0.f;

			vDir.Normalize();

			pMonster->SetActorRotation(vDir.Rotation());
		}

		return EBTNodeResult::Failed;
	}

	pMonster->Add_AttackEndFunction<UBTTask_Attack>(this, &UBTTask_Attack::AttackEnd);

	m_isAttackEnd = false;

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	AMonster* pMonster = pController->GetPawn<AMonster>();

	FString type = pMonster->Get_AnimType();

	if (TEXT("Death") != type && TEXT("Hit") != type
		&& ECharacterState::Running == pMonster->Get_State())
	{
		pMonster->Set_AnimType(TEXT("Attack"));
		
		AActor* pTarget = Cast<AActor>(pController->GetBlackboardDataAsObject(AMonsterAIController::m_TargetKey));

		if (IsValid(pTarget))
		{
			FVector vDir = pTarget->GetActorLocation() - pMonster->GetActorLocation();

			vDir.Z = 0.f;

			vDir.Normalize();

			pMonster->SetActorRotation(vDir.Rotation());
		}
	}

	if (true == m_isAttackEnd)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		pMonster->Set_AnimType(TEXT("Idle"));
	}
}

void UBTTask_Attack::AttackEnd()
{
	m_isAttackEnd = true;
}