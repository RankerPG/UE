#include "BTService_Detect.h"
#include "MonsterAIController.h"
#include "Monster.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!pController)
		return;

	AMonster* pMonster = Cast<AMonster>(pController->GetPawn());

	if (!pMonster)
		return;

	FCollisionQueryParams tParams(NAME_None, false, pMonster);

	TArray<FOverlapResult> arrResult;

	float fTraceRange = pController->GetBlackboardDataAsFloat(AMonsterAIController::m_TraceRangeKey);

	bool bCollision = GetWorld()->OverlapMultiByChannel(arrResult, pMonster->GetActorLocation(),
		FQuat::Identity, (ECollisionChannel)CollisionMonsterDetect, FCollisionShape::MakeSphere(fTraceRange), tParams);

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = bCollision ? FColor::Red : FColor::Blue;

	DrawDebugSphere(GetWorld(), pMonster->GetActorLocation(), fTraceRange, 10, DrawColor, false, 1.f);

#endif

	if (bCollision)
	{
		pController->SetBlackboardDataAsObject(AMonsterAIController::m_TargetKey, arrResult[0].GetActor());
	}
	else
	{
		pController->SetBlackboardDataAsObject(AMonsterAIController::m_TargetKey, nullptr);

		pMonster->Set_AnimSequence(TEXT("Idle"));
	}
}