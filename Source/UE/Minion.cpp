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

	ConstructorHelpers::FClassFinder<AActor> BulletFinder(TEXT("Blueprint'/Game/Monster/BP_Bullet.BP_Bullet_C'"));

	if (BulletFinder.Succeeded())
	{
		m_BulletClass = BulletFinder.Class;
	}

	m_strMonsterName = TEXT("Minion");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMinionAIController::StaticClass();
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

void AMinion::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	m_pController = Cast<AMinionAIController>(NewController);
}

void AMinion::Shot_Bullet()
{
	if (!IsValid(m_pController))
		return;

	if (!IsValid(m_pMesh))
		return;

	FVector vLoc, vTargetPos;

	AActor* pTarget = Cast<AActor>(m_pController->GetBlackboardDataAsObject(AMonsterAIController::m_TargetKey));

	if (IsValid(pTarget))
	{
		vTargetPos = pTarget->GetActorLocation() + FVector(0.f, 0.f, -100.f);
	}

	vLoc = m_pMesh->GetSocketByName(TEXT("Muzzle_Front"))->GetSocketLocation(m_pMesh);

	FVector vDir = vTargetPos - vLoc;

	vDir.Normalize();

	FRotator rotForMesh(0.f, -90.f, 0.f);

	FRotator rot = rotForMesh + vDir.Rotation();

	FActorSpawnParameters tParam;

	tParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* pBullet = GetWorld()->SpawnActor(m_BulletClass, &vLoc, &rot, tParam);
}