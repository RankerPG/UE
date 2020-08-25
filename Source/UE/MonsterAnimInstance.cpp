#include "MonsterAnimInstance.h"
#include "Minion.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	m_strCurrentAnimType = TEXT("Idle");

	m_strArray.Add(TEXT("Idle"));
	m_strArray.Add(TEXT("Patrol"));
	m_strArray.Add(TEXT("Run"));
	m_strArray.Add(TEXT("Attack"));
	m_strArray.Add(TEXT("Hit"));
	m_strArray.Add(TEXT("Death"));
	m_strArray.Add(TEXT("Stun"));

	m_strIdle = m_strArray[0];
	m_strPatrol = m_strArray[1];
	m_strRun = m_strArray[2];
	m_strAttack = m_strArray[3];
	m_strHit = m_strArray[4];
	m_strDeath = m_strArray[5];
	m_strStun = m_strArray[6];
}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	m_pMonster = Cast<AMonster>(TryGetPawnOwner());
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(m_pMonster))
	{
		if (m_strArray[(int)EMonsterAnimType::Death] == m_strCurrentAnimType)
			return;

		float fSpeed = m_pMonster->GetVelocity().Size();

		if (0.f < fSpeed)
		{

		}
		else
		{
			if (m_strRun == m_strCurrentAnimType || m_strPatrol == m_strCurrentAnimType)
			{
				m_strCurrentAnimType = m_strArray[(int)EMonsterAnimType::Idle];
			}
		}
	}
}

void UMonsterAnimInstance::AnimNotify_ActionToIdle()
{
	m_strCurrentAnimType = m_strArray[(int)EMonsterAnimType::Idle];
}

void UMonsterAnimInstance::AnimNotify_DeathEnd()
{
	AMonster* pMonster = Cast<AMonster>(TryGetPawnOwner());

	if (IsValid(pMonster))
	{
		pMonster->DeathEnd();
	}
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	AMonster* pMonster = Cast<AMonster>(TryGetPawnOwner());

	if (IsValid(pMonster))
	{
		pMonster->AttackEnd();
	}
}

void UMonsterAnimInstance::AnimNotify_ShotBullet()
{
	AMinion* pMonster = Cast<AMinion>(TryGetPawnOwner());

	if (IsValid(pMonster))
	{
		pMonster->Shot_Bullet();
	}
}

void UMonsterAnimInstance::AnimNotify_CollisionCheck()
{
	AMinion* pMonster = Cast<AMinion>(TryGetPawnOwner());

	if (IsValid(pMonster))
	{
		FHitResult result;

		pMonster->CollisionCheck(result);
	}
}