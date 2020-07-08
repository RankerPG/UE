// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	m_strCurrentAnimType = TEXT("Idle");

	m_strArray.Add(TEXT("Idle"));
	m_strArray.Add(TEXT("Run"));
	m_strArray.Add(TEXT("Attack"));
	m_strArray.Add(TEXT("Death"));
	m_strArray.Add(TEXT("Jump"));
	m_strArray.Add(TEXT("Skill"));

	m_strIdle = m_strArray[0];
	m_strRun = m_strArray[1];
	m_strAttack = m_strArray[2];
	m_strDeath = m_strArray[3];
	m_strJump = m_strArray[4];
	m_strSkill = m_strArray[5];

	m_iAttack = (int32)EAttackType::AttackNone;

	m_isAttackEnable = true;

	m_isFalling = false;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());
	
	if (IsValid(pPlayer))
	{
		float fSpeed = pPlayer->GetVelocity().Size();

		m_isFalling = pPlayer->GetCharacterMovement()->IsFalling();

		if (true == m_isFalling && m_strArray[(int)EPlayerAnimType::Jump] != m_strCurrentAnimType)
		{
			m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Jump];
		}

		if (m_strArray[(int)EPlayerAnimType::Attack] == m_strCurrentAnimType)
		{
			
		}
		else if (m_strArray[(int)EPlayerAnimType::Skill] == m_strCurrentAnimType)
		{

		}
		else
		{
			if (m_strArray[(int)EPlayerAnimType::Jump] == m_strCurrentAnimType)
			{

			}
			else
			{
				if (0 < fSpeed)
				{
					m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Run];
				}
				else
				{
					m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Idle];
				}
			}
		}
	}
}

void UPlayerAnimInstance::AnimNotify_AttackToIdle()
{
	m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Idle];
	m_isAttackEnable = true;
	m_iAttack = 0;
}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	m_isAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_JumpToIdle()
{
	m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Idle];
	m_isAttackEnable = true;
	m_iAttack = 0;
}

void UPlayerAnimInstance::AnimNotify_Fireball()
{
	auto pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		pPlayer->Fireball();
	}
}

void UPlayerAnimInstance::Set_AttackType()
{
	if (m_isAttackEnable)
	{
		m_isAttackEnable = false;

		switch (m_iAttack)
		{
		case (int32)EAttackType::AttackNone:
			m_iAttack = (int32)EAttackType::Attack1;
			break;
		case (int32)EAttackType::Attack1:
			m_iAttack = (int32)EAttackType::Attack2;
			break;
		case (int32)EAttackType::Attack2:
			m_iAttack = (int32)EAttackType::Attack3;
			break;
		case (int32)EAttackType::Attack3:
			m_iAttack = (int32)EAttackType::Attack4;
			break;
		}
	}
}
