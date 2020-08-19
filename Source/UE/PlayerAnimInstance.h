// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "info.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class UE_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	FString Get_AnimType() { return m_strCurrentAnimType; }

	ERunType Get_RunType() { return m_eRunType; }

	void Set_AnimType(EPlayerAnimType eAnimType) { m_strCurrentAnimType = m_strArray[(int)eAnimType]; }

	void Set_AttackType();

	void Set_RunType(ERunType eRunType) { m_eRunType = eRunType; }

public:
	UFUNCTION()
		void AnimNotify_AttackToIdle();

	UFUNCTION()
		void AnimNotify_AttackEnable();

	UFUNCTION()
		void AnimNotify_JumpToIdle();

	UFUNCTION()
		void AnimNotify_ActionToIdle();

	UFUNCTION()
		void AnimNotify_Fireball();

	UFUNCTION()
		void AnimNotify_CollisionCheck();

	UFUNCTION()
		void AnimNotify_Dash();

	UFUNCTION()
		void AnimNotify_DashEnd();

public:
	UPlayerAnimInstance();

private:
	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

protected:
	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_strCurrentAnimType;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strIdle;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strRun;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strAttack;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strDeath;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strJump;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strHit;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strDash;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strSkill;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strSkill2;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strSkill3;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strSkill4;

	TArray<FString>m_strArray;

	//
	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32 m_iAttack;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32 m_iDir;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		ERunType m_eRunType;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool m_isFalling;

	bool m_isAttackEnable;
};
