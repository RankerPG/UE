// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
#include "EffectSound.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	m_strCurrentAnimType = TEXT("Idle");

	m_strArray.Add(TEXT("Idle"));
	m_strArray.Add(TEXT("Run"));
	m_strArray.Add(TEXT("Attack"));
	m_strArray.Add(TEXT("Death"));
	m_strArray.Add(TEXT("Jump"));
	m_strArray.Add(TEXT("Hit"));
	m_strArray.Add(TEXT("Dash"));
	m_strArray.Add(TEXT("Skill"));
	m_strArray.Add(TEXT("Skill2"));
	m_strArray.Add(TEXT("Skill3"));
	m_strArray.Add(TEXT("Skill4"));

	m_strIdle = m_strArray[0];
	m_strRun = m_strArray[1];
	m_strAttack = m_strArray[2];
	m_strDeath = m_strArray[3];
	m_strJump = m_strArray[4];
	m_strHit = m_strArray[5];
	m_strDash = m_strArray[6];
	m_strSkill = m_strArray[7];
	m_strSkill2 = m_strArray[8];
	m_strSkill3 = m_strArray[9];
	m_strSkill4 = m_strArray[10];

	m_iAttack = (int32)EAttackType::AttackNone;

	m_iDir = 0;

	m_eRunType = ERunType::RunNone;

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
		else if (m_strArray[(int)EPlayerAnimType::Dash] == m_strCurrentAnimType)
		{

		}
		else
		{
			if (m_strArray[(int)EPlayerAnimType::Jump] == m_strCurrentAnimType)
			{

			}
			else
			{
				if (0.f < fSpeed)
				{
					m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Run];
				}
				else if (m_strArray[(int)EPlayerAnimType::Hit] != m_strCurrentAnimType
					&& m_strArray[(int)EPlayerAnimType::Dash] != m_strCurrentAnimType)
				{
					m_eRunType = ERunType::RunNone;

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

void UPlayerAnimInstance::AnimNotify_ActionToIdle()
{
	m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Idle];
}

void UPlayerAnimInstance::AnimNotify_Fireball()
{
	auto pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		pPlayer->Fireball();
	}
}

void UPlayerAnimInstance::AnimNotify_CollisionCheck()
{
	auto pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		TArray<FHitResult> resultArray;

		bool bCollision = pPlayer->CollisionCheck(resultArray);

		if (bCollision)
		{
			for (auto& result : resultArray)
			{
				FActorSpawnParameters tSpawnParams;

				tSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				AEffectSound* pSound = GetWorld()->SpawnActor<AEffectSound>(result.ImpactPoint, result.ImpactNormal.Rotation(), tSpawnParams);

				switch (m_iAttack)
				{
				case (int32)EAttackType::Attack1:
					pSound->LoadAudio(TEXT("SoundWave'/Game/Sound/Hit_SwordStabEarth_Rumble1.Hit_SwordStabEarth_Rumble1'"));
					break;
				case (int32)EAttackType::Attack2:
					pSound->LoadAudio(TEXT("SoundWave'/Game/Sound/Hit_SwordStabEarth_Rumble2.Hit_SwordStabEarth_Rumble2'"));
					break;
				case (int32)EAttackType::Attack3:
					pSound->LoadAudio(TEXT("SoundWave'/Game/Sound/Hit_SwordStabEarth_Rumble3.Hit_SwordStabEarth_Rumble3'"));
					break;
				case (int32)EAttackType::Attack4:
					pSound->LoadAudio(TEXT("SoundWave'/Game/Sound/Hit_SwordReboundForcefield.Hit_SwordReboundForcefield'"));
					break;
				default:
					pSound->LoadAudio(TEXT("SoundWave'/Game/Sound/Hit_SwordStabEarth_Rumble1.Hit_SwordStabEarth_Rumble1'"));
					break;
				}

				pSound->Play();
			}
		}
	}
}

void UPlayerAnimInstance::AnimNotify_Dash()
{
	auto pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		pPlayer->Move_Dash();
	}
}

void UPlayerAnimInstance::AnimNotify_DashEnd()
{
	auto pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(pPlayer))
	{
		pPlayer->Dash_End();
	}
}

void UPlayerAnimInstance::AnimNotify_AttackToDash()
{
	m_strCurrentAnimType = m_strDash;
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
