#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
#include "EffectSound.h"
#include "MaterialSound.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	m_strCurrentAnimType = TEXT("Idle");

	m_strArray.Add(TEXT("Idle"));
	m_strArray.Add(TEXT("Run"));
	m_strArray.Add(TEXT("Attack"));
	m_strArray.Add(TEXT("Death"));
	m_strArray.Add(TEXT("Jump"));
	m_strArray.Add(TEXT("Evade"));
	m_strArray.Add(TEXT("Skill_Q"));
	m_strArray.Add(TEXT("Skill_E"));
	m_strArray.Add(TEXT("Skill_R"));

	m_strIdle = m_strArray[0];
	m_strRun = m_strArray[1];
	m_strAttack = m_strArray[2];
	m_strDeath = m_strArray[3];
	m_strJump = m_strArray[4];
	m_strEvade = m_strArray[5];
	m_strSkill_Q = m_strArray[6];
	m_strSkill_E = m_strArray[7];
	m_strSkill_R = m_strArray[8];

	m_iDir = 0;

	m_eRunType = ERunType::RunNone;

	m_fSpeed = 0.f;

	m_isJumpEnable = true;

	m_isFalling = false;

	m_isJumpAttack = false;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	m_pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());

	m_fPlayRate = 1.f;

	m_pMaterialSound = NewObject<UMaterialSound>(this, TEXT("MaterialSound"));

	m_pMaterialSound->Load_Sound(TEXT("PMT_Grass"), TEXT("SoundWave'/Game/Sound/Foot_Glass_HeelsRun24.Foot_Glass_HeelsRun24'"));
	m_pMaterialSound->Load_Sound(TEXT("PMT_GrassL"), TEXT("SoundWave'/Game/Sound/Foot_Glass_HeelsRun25.Foot_Glass_HeelsRun25'"));
	m_pMaterialSound->Load_Sound(TEXT("PMT_Desert"), TEXT("SoundWave'/Game/Sound/Foot_Mud_Run01.Foot_Mud_Run01'"));
	m_pMaterialSound->Load_Sound(TEXT("PMT_DesertL"), TEXT("SoundWave'/Game/Sound/Foot_Mud_Run02.Foot_Mud_Run02'"));
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(m_pPlayer))
	{
		if (ECharacterState::Running != m_pPlayer->Get_State())
			return;

		m_fSpeed = m_pPlayer->GetVelocity().Size();

		m_isAccelerating = 0.f == m_fSpeed ? false : true;

		m_isFalling = m_pPlayer->GetMovementComponent()->IsFalling();

		if (true == m_isFalling && m_strArray[(int)EPlayerAnimType::Jump] != m_strCurrentAnimType)
		{
			m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Jump];
		}

		if (m_strArray[(int)EPlayerAnimType::Skill_Q] == m_strCurrentAnimType)
		{
			StopAllMontages(0.1f);

			m_pPlayer->SkillQ_Move();
		}
		else if (m_strArray[(int)EPlayerAnimType::Skill_E] == m_strCurrentAnimType)
		{
			StopAllMontages(0.f);
		}
		else if (m_strArray[(int)EPlayerAnimType::Skill_R] == m_strCurrentAnimType)
		{
		}
		else if (m_strArray[(int)EPlayerAnimType::Evade] == m_strCurrentAnimType)
		{
			StopAllMontages(0.1f);

			m_pPlayer->Evade_Move();
		}
		else
		{
			if (m_strArray[(int)EPlayerAnimType::Jump] != m_strCurrentAnimType)
			{
				if (0.f < m_fSpeed)
				{
					m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Run];
				}
				else
				{
					m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Idle];

					m_eRunType = ERunType::RunNone;
				}
			}
		}
	}
}

void UPlayerAnimInstance::Add_Yaw(float fDirection)
{
	float fDelta = GetWorld()->GetDeltaSeconds();

	float fPerYaw = 450.f; // 0.1초에 45도 회전

	if (0.f == fDirection)
	{
		if (m_fYaw > 5.f)
			m_fYaw -= fPerYaw * fDelta;
		else if(m_fYaw < -5.f)
			m_fYaw += fPerYaw * fDelta;
		else
			m_fYaw = 0.f;
	}

	m_fYaw += fPerYaw * fDirection * fDelta;

	if (-45.f > m_fYaw)
		m_fYaw = -45.f;
	else if (45.f < m_fYaw)
		m_fYaw = 45.f;
}

void UPlayerAnimInstance::PlayFootSound(const FName& strName, bool isRight)
{
	USkeletalMeshComponent* pMesh = m_pPlayer->GetMesh();

	FTransform socketTrans = pMesh->GetSocketTransform(strName);

	FVector vStart = socketTrans.GetLocation() - FVector::UpVector * 1000.f;

	FVector vEnd = vStart + FVector::UpVector * 2000.f;

	FHitResult result;
	TArray<AActor*> ignoreActor;
	ignoreActor.Add(m_pPlayer);

	bool isResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(), vStart, vEnd, UEngineTypes::ConvertToTraceType(ECC_WorldStatic), false
		, ignoreActor, EDrawDebugTrace::None, result, true);

	static int cnt = 0;

	if (true == isResult)
	{
		if (!IsValid(result.GetActor()))
			return;

		FString strSoundName = result.PhysMaterial->GetName();

		if (false == isRight)
			strSoundName += TEXT("L");

		LOGW("%s", *strSoundName);

		USoundBase* pSoundBase = m_pMaterialSound->Find_Sound(strSoundName);

		if (IsValid(pSoundBase))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pSoundBase, result.ImpactPoint, 0.25f);
		}
	}
}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	m_pPlayer->Reset_AttackInfo();
}

void UPlayerAnimInstance::AnimNotify_JumpEntry()
{
	m_isJumpEnable = false;
}

void UPlayerAnimInstance::AnimNotify_JumpToIdle()
{
	m_strCurrentAnimType = m_strArray[(int)EPlayerAnimType::Idle];
}

void UPlayerAnimInstance::AnimNotify_JumpEnd()
{
	m_isJumpEnable = true;

	m_isJumpAttack = false;
}

void UPlayerAnimInstance::AnimNotify_Fireball()
{
	if (IsValid(m_pPlayer))
	{
		m_pPlayer->Fireball();
	}
}

void UPlayerAnimInstance::AnimNotify_CollisionCheck()
{
	if (IsValid(m_pPlayer))
	{
		TArray<FHitResult> resultArray;

		bool bCollision = m_pPlayer->CollisionCheck(resultArray);

		if (bCollision)
		{
			int iAttackCombo = m_pPlayer->Get_AttackCombo();

			for (auto& result : resultArray)
			{
				FActorSpawnParameters tSpawnParams;

				tSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				AEffectSound* pSound = GetWorld()->SpawnActor<AEffectSound>(result.ImpactPoint, result.ImpactNormal.Rotation(), tSpawnParams);

				switch (iAttackCombo)
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
					pSound->LoadAudio(TEXT("SoundWave'/Game/Sound/Hit_SwordStabEarth_Rumble3.Hit_SwordStabEarth_Rumble3'"));
					break;
				}

				if (m_strSkill_Q == m_strCurrentAnimType)
				{
					pSound->LoadAudio(TEXT("SoundWave'/Game/Sound/QHit.QHit'"));
				}

				pSound->Play();
			}
		}
	}
}

void UPlayerAnimInstance::AnimNotify_CollisionCheck_Sphere()
{
	if (IsValid(m_pPlayer))
	{
		TArray<FHitResult> resultArray;

		bool bCollision = m_pPlayer->CollisionCheck_Sphere(resultArray);

		if (bCollision)
		{
			for (auto& result : resultArray)
			{

			}
		}
	}
}

void UPlayerAnimInstance::AnimNotify_EvadeEnd()
{
	m_pPlayer->Set_Evading(false);
}

void UPlayerAnimInstance::AnimNotify_AttackToDash()
{
	m_strCurrentAnimType = m_strEvade;
}

void UPlayerAnimInstance::AnimNotify_SkillQMovingOnOff()
{
	m_pPlayer->Set_SkillQMoving();
}

void UPlayerAnimInstance::AnimNotify_CreateFrozenDecal()
{
	m_pPlayer->SkillR_FrozenWorld();
}

void UPlayerAnimInstance::AnimNotify_IceSpike()
{
	m_pPlayer->SkillE_SpikeCircle();
}

void UPlayerAnimInstance::AnimNotify_PlayFootSound()
{
	PlayFootSound(TEXT("Foot_R"), true);
}

void UPlayerAnimInstance::AnimNotify_PlayFootSound_L()
{
	PlayFootSound(TEXT("Foot_L"), false);
}