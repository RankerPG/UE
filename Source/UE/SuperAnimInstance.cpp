#include "SuperAnimInstance.h"


USuperAnimInstance::USuperAnimInstance()
{

}

void USuperAnimInstance::Set_Frozen(float fFrozenTime)
{
	m_eState = ECharacterState::Frozen;

	m_pCharacter->GetMesh()->bPauseAnims = true;

	m_pCharacter->GetWorldTimerManager().SetTimer(m_FrozenTimerHandle, this, &USuperAnimInstance::FrozenEnd, fFrozenTime, false);
}


void USuperAnimInstance::Set_Stun(float fStunTime)
{
	m_eState = ECharacterState::Stun;

	m_pCharacter->GetMesh()->bPauseAnims = false;

	m_pCharacter->GetWorldTimerManager().SetTimer(m_StunTimerHandle, this, &USuperAnimInstance::StunEnd, fStunTime, false);
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
	m_eState = ECharacterState::Running;

	m_pCharacter->GetMesh()->bPauseAnims = false;
}

void USuperAnimInstance::StunEnd()
{
	m_eState = ECharacterState::Running;
}