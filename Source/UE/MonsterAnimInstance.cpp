#include "MonsterAnimInstance.h"
#include "Monster.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	m_strCurrentAnimType = TEXT("Idle");

	m_strArray.Add(TEXT("Idle"));
	m_strArray.Add(TEXT("Run"));
	m_strArray.Add(TEXT("Attack"));
	m_strArray.Add(TEXT("Hit"));
	m_strArray.Add(TEXT("Death"));

	m_strIdle = m_strArray[0];
	m_strRun = m_strArray[1];
	m_strAttack = m_strArray[2];
	m_strHit = m_strArray[3];
	m_strDeath = m_strArray[4];
}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pMonster = Cast<AMonster>(TryGetPawnOwner());

	if (IsValid(pMonster))
	{
		float fSpeed = pMonster->GetVelocity().Size();

		if (m_strArray[(int)EMonsterAnimType::Attack] == m_strCurrentAnimType)
		{

		}
		else
		{
			if (0 < fSpeed)
			{
				m_strCurrentAnimType = m_strArray[(int)EMonsterAnimType::Run];
			}
			else
			{
				m_strCurrentAnimType = m_strArray[(int)EMonsterAnimType::Idle];
			}
		}
	}
}

void UMonsterAnimInstance::AnimNotify_HitToIdle()
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

void UMonsterAnimInstance::Set_AnimName(const FString& strName)
{
	m_strCurrentAnimType = strName;
}