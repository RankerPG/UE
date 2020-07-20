#include "BTDecorator_InAttackRange.h"
#include "MonsterAIController.h"
#include "BehaviorTree//BlackboardComponent.h"
#include "BehaviorTree//BehaviorTreeComponent.h"
#include "GameFramework/Character.h"

UBTDecorator_InAttackRange::UBTDecorator_InAttackRange()
{
	NodeName = TEXT("InAttackRange");
}

bool UBTDecorator_InAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!pController)
		return false;

	ACharacter* pTarget = Cast<ACharacter>(pController->GetBlackboardDataAsObject(AMonsterAIController::m_TargetKey));

	if (!pTarget)
		return false;

	ACharacter* pMonster = pController->GetPawn<ACharacter>();

	if (!pMonster)
		return false;

	FVector vMonsterPos = pMonster->GetMesh()->GetComponentLocation();
	FVector vTargetPos = pTarget->GetMesh()->GetComponentLocation();

	float fDist = FVector::Distance(vMonsterPos, vTargetPos);

	float fAttackRange = pController->GetBlackboardDataAsFloat(AMonsterAIController::m_AttackRangeKey);

	return fDist <= fAttackRange;
}
