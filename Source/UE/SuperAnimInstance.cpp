#include "SuperAnimInstance.h"
#include "SkillEffect.h"

USuperAnimInstance::USuperAnimInstance()
{

}

void USuperAnimInstance::Set_Frozen(float fFrozenTime)
{
	m_eState = ECharacterState::Frozen;

	if (true == m_FrozenTimerHandle.IsValid())
		m_pCharacter->GetWorldTimerManager().ClearTimer(m_FrozenTimerHandle);

	m_pCharacter->GetWorldTimerManager().SetTimer(m_FrozenTimerHandle, this, &USuperAnimInstance::FrozenEnd, fFrozenTime, false);
}


void USuperAnimInstance::Set_Stun(float fStunTime)
{
	m_eState = ECharacterState::Stun;

	if (true == m_StunTimerHandle.IsValid())
		m_pCharacter->GetWorldTimerManager().ClearTimer(m_StunTimerHandle);

	m_pCharacter->GetWorldTimerManager().SetTimer(m_StunTimerHandle, this, &USuperAnimInstance::StunEnd, fStunTime, false);
}

void USuperAnimInstance::Set_Knockback(float fKnockbackTime)
{
	m_eState = ECharacterState::Knockback;

	if (true == m_FrozenTimerHandle.IsValid())
		m_pCharacter->GetWorldTimerManager().ClearTimer(m_KnockbackTimerHandle);

	m_pCharacter->GetWorldTimerManager().SetTimer(m_KnockbackTimerHandle, this, &USuperAnimInstance::KnockbackEnd, fKnockbackTime, false);
}

void USuperAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	m_pCharacter = Cast<ACharacter>(TryGetPawnOwner());

	m_strCurrentAnimType = TEXT("Idle");

	m_eState = ECharacterState::Running;

	m_fPlayRate = 1.f;
}

void USuperAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void USuperAnimInstance::AnimNotify_ActionToIdle()
{
	m_strCurrentAnimType = TEXT("Idle");
}

void USuperAnimInstance::AnimNotify_ChangePlayRate_100()
{
	m_fPlayRate = 1.f;
}

void USuperAnimInstance::AnimNotify_ChangePlayRate_200()
{
	m_fPlayRate = 2.f;
}

void USuperAnimInstance::FrozenEnd()
{
	if(ECharacterState::Frozen == m_eState)
		m_eState = ECharacterState::Running;

	m_pCharacter->GetWorldTimerManager().ClearTimer(m_FrozenTimerHandle);
}

void USuperAnimInstance::StunEnd()
{
	if (ECharacterState::Stun == m_eState)
		m_eState = ECharacterState::Running;

	m_pCharacter->GetWorldTimerManager().ClearTimer(m_StunTimerHandle);
}

void USuperAnimInstance::KnockbackEnd()
{
	if (ECharacterState::Knockback == m_eState)
		m_eState = ECharacterState::Running;

	m_pCharacter->GetWorldTimerManager().ClearTimer(m_KnockbackTimerHandle);
}