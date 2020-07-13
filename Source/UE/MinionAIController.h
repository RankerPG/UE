#pragma once

#include "info.h"
#include "MonsterAIController.h"
#include "MinionAIController.generated.h"

UCLASS()
class UE_API AMinionAIController : public AMonsterAIController
{
	GENERATED_BODY()
	
public:
	AMinionAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void SetBlackBoardInitiallizeData(APawn* InPawn);
};
