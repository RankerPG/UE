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
	void Set_AnimType(EPlayerAnimType eAnimType) { m_strCurrentAnimType = m_strArray[(int)eAnimType]; }

	void Set_AttackType();

	UFUNCTION()
	void AnimNotify_AttackToIdle();

	UFUNCTION()
	void AnimNotify_AttackEnable();

	UFUNCTION()
	void AnimNotify_JumpToIdle();

	UFUNCTION()
	void AnimNotify_Fireball();

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
	FString m_strSkill;

	TArray<FString>m_strArray;

	//
	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 m_iAttack;

	bool m_isAttackEnable;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool m_isFalling;
};
