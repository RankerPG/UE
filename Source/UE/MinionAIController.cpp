#include "MinionAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMinionAIController::AMinionAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTFinder(TEXT("BehaviorTree'/Game/Monster/BT_Minion.BT_Minion'"));

	if (BTFinder.Succeeded())
	{
		m_pBT = BTFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData>  BBFinder(TEXT("BlackboardData'/Game/Monster/BB_Minion.BB_Minion'"));

	if (BBFinder.Succeeded())
	{
		m_pBB = BBFinder.Object;
	}
}

void AMinionAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(m_pBB, Blackboard))
	{
		SetBlackBoardInitiallizeData(InPawn);

		if (!RunBehaviorTree(m_pBT))
		{
			
		}
	}
}

void AMinionAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMinionAIController::SetBlackBoardInitiallizeData(APawn* InPawn)
{
	Super::SetBlackBoardInitiallizeData(InPawn);
}
