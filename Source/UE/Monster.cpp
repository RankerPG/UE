#include "Monster.h"
#include "MonsterAnimInstance.h"
#include "SpawnPoint.h"
#include "UEGameInstance.h"
#include "MinionAIController.h"
#include "DrawDebugHelpers.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMonster::CollsionHit);

	m_pAnim = nullptr;

	m_iPatrolNum = 0;
}

FString& AMonster::Get_AnimSequence()
{
	return m_pAnim->Get_AnimName();
}

const FVector& AMonster::Get_NextPatrolPos()
{
	m_iPatrolNum = (++m_iPatrolNum) % m_PatrolPosArray.Num();

	return m_PatrolPosArray[m_iPatrolNum];
}

void AMonster::Set_AnimSequence(const FString& strAnim)
{
	m_pAnim->Set_AnimName(strAnim);
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(m_pSpawnPoint))
	{
		m_pSpawnPoint->CallSpawnTimer();
	}
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//GetWorldTimerManager()->Set
}

void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FMonsterInfo* info = Cast<UUEGameInstance>(GetGameInstance())->FindMonsterInfo(*m_strMonsterName);

	if (nullptr != info)
	{
		m_fTraceRange = info->TraceRange;
		m_fAttackRange = info->AttackRange;
		m_fAttackDelay = info->AttackDelay;
		m_fAttackPoint = info->AttackPoint;
		m_fArmorPoint = info->ArmorPoint;
		m_fHP = m_fMaxHP = info->HP;
		m_fMP = m_fMaxMP = info->MP;
		m_iLevel = info->Level;
		m_iExp = info->Exp;
		m_iGold = info->Gold;
	}
}

void AMonster::UnPossessed()
{
}

float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (fDamage > 0.f)
	{
		fDamage -= m_fArmorPoint;

		fDamage = fDamage <= 0.f ? 1.f : fDamage;

		m_fHP -= fDamage;

		//LOG(Warning, TEXT("%f"), m_fHP);

		if (m_fHP > 0.f)
		{
			m_pAnim->Set_AnimName(TEXT("Hit"));
		}
		else
		{
			m_pAnim->Set_AnimName(TEXT("Death"));

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	return fDamage;
}

void AMonster::CollsionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void AMonster::Death()
{

}

void AMonster::DeathEnd()
{
	Destroy();
}

void AMonster::AttackEnd()
{
	m_OnAttackEnd.Broadcast();

	for (FDelegateHandle handle : m_AttackEndHandleArray)
	{
		m_OnAttackEnd.Remove(handle);
	}
}

bool AMonster::CollisionCheck(FHitResult& resultOut)
{
	FCollisionQueryParams tParam(NAME_None, false, this);

	FVector vLoc = GetActorLocation();
	FVector vForward = GetActorForwardVector();

	bool bCollision = GetWorld()->SweepSingleByChannel(resultOut, vLoc, vLoc + vForward * m_fAttackRange,
		FQuat::Identity, (ECollisionChannel)CollisionMonsterAttack, FCollisionShape::MakeSphere(50.f), tParam);

#if ENABLE_DRAW_DEBUG

	FVector vCenter = vLoc + vForward * (m_fAttackRange / 2.f);

	FColor DrawColor = bCollision ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), vCenter, m_fAttackRange / 2.f, 50.f, FRotationMatrix::MakeFromZ(vForward).ToQuat()
		, DrawColor, false, 0.5f);

#endif

	if (bCollision)
	{
		FDamageEvent damageEvent;

		//Damage parameter
		resultOut.GetActor()->TakeDamage(20.f, damageEvent, m_pController, this);

		// Add Effect
	}

	return true;
}