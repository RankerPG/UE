#include "Minion.h"
#include "MonsterAnimInstance.h"

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

	m_fAttackRange = 50.f;
	m_fAttackPoint = 10.f;
	m_fArmorPoint = 10.f;
	m_fHP = m_fMaxHP = 100.f;
	m_fMP = m_fMaxMP = 50.f;
	m_iLevel = 1;
	m_iExp = 100;
	m_iGold = 1000;
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
