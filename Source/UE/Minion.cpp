#include "Minion.h"
#include "MonsterAnimInstance.h"
#include "MinionAIController.h"

AMinion::AMinion()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Super_Core_Dawn.Minion_Lane_Super_Core_Dawn'"));

	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
	}

	ConstructorHelpers::FClassFinder<UMonsterAnimInstance> AnimFinder(TEXT("AnimBlueprint'/Game/Monster/BP_MinionAnim.BP_MinionAnim_C'"));

	if (AnimFinder.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimFinder.Class);
	}

	m_strMonsterName = TEXT("Minion");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMinionAIController::StaticClass();

	LOG(Warning, TEXT("Constructor Call"));
}

void AMinion::BeginPlay()
{
	Super::BeginPlay();

	m_pAnim = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
}

void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
