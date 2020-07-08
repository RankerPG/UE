#include "MonsterAnimInstance.h"
#include "Monster.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	m_strCurrentAnimType = TEXT("Idle");

	m_strArray.Add(TEXT("Idle"));
	m_strArray.Add(TEXT("Attack"));
	m_strArray.Add(TEXT("Hit"));
	m_strArray.Add(TEXT("Death"));

	m_strIdle = m_strArray[0];
	m_strAttack = m_strArray[1];
	m_strHit = m_strArray[2];
	m_strDeath = m_strArray[3];
}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMonsterAnimInstance::AnimNotify_HitToIdle()
{
	m_strCurrentAnimType = m_strArray[0];
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