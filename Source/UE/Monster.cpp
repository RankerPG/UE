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

	//GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMonster::CollsionHit);

	m_pAnim = nullptr;

	m_pMesh = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	m_iPatrolNum = 0;

	m_isAttackEnable = true;
}

FString AMonster::Get_AnimType()
{
	return m_pAnim->Get_AnimType();
}

const FVector& AMonster::Get_NextPatrolPos()
{
	m_iPatrolNum = (++m_iPatrolNum) % m_PatrolPosArray.Num();

	return m_PatrolPosArray[m_iPatrolNum];
}

ECharacterState AMonster::Get_State()
{
	if (!IsValid(m_pAnim))
		return ECharacterState::StateNone;

	return m_pAnim->Get_State();
}

void AMonster::Set_AnimType(const FString& strAnim)
{
	m_pAnim->Set_AnimType(strAnim);
}

void AMonster::Set_Frozen(float fFrozenTime)
{
	m_pAnim->Set_Frozen(fFrozenTime);
}

void AMonster::Set_Stun(float fStunTime)
{
	m_pAnim->Set_Stun(fStunTime);
}

void AMonster::Set_Knockback(float fKnockbackTime)
{
	m_pAnim->Set_Knockback(fKnockbackTime);
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
			if (ECharacterState::Running == m_pAnim->Get_State())
				m_pAnim->Set_AnimType(TEXT("Hit"));
		}
		else
		{
			m_pAnim->Set_AnimType(TEXT("Death"));

			m_pAnim->Set_State(ECharacterState::Running);

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			m_pMesh->bPauseAnims = false;
		}
	}

	return fDamage;
}

void AMonster::DeathEnd()
{
	Destroy();
}

void AMonster::AttackDelay()
{
	GetWorldTimerManager().ClearTimer(m_AttackDelayTimerHandle);

	m_isAttackEnable = true;
}

void AMonster::AttackEnd()
{
	m_OnAttackEnd.Broadcast();

	for (FDelegateHandle handle : m_AttackEndHandleArray)
	{
		m_OnAttackEnd.Remove(handle);
	}

	GetWorldTimerManager().SetTimer(m_AttackDelayTimerHandle, this, &AMonster::AttackDelay, m_fAttackDelay, false);
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