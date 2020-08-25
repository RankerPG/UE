#pragma once

#include "info.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class UE_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

public:
	FString Get_AnimType() { return m_strCurrentAnimType; }
	ERunType Get_RunType() { return m_eRunType; }
	bool Get_JumpEnable() { return m_isJumpEnable; }

	void Set_AnimType(EPlayerAnimType eAnimType) { m_strCurrentAnimType = m_strArray[(int)eAnimType]; }
	void Set_RunType(ERunType eRunType) { m_eRunType = eRunType; }
	void Add_Yaw(float fDirection);

public:
	UFUNCTION()
		void AnimNotify_AttackEnable();

	UFUNCTION()
		void AnimNotify_JumpEntry();

	UFUNCTION()
		void AnimNotify_JumpToIdle();

	UFUNCTION()
		void AnimNotify_JumpEnd();

	UFUNCTION()
		void AnimNotify_ActionToIdle();

	UFUNCTION()
		void AnimNotify_Fireball();

	UFUNCTION()
		void AnimNotify_CollisionCheck();

	UFUNCTION()
		void AnimNotify_EvadeEnd();

	UFUNCTION()
		void AnimNotify_AttackToDash();

private:
	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

protected:
	class APlayerCharacter* m_pPlayer;

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
		FString m_strStun;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strEvade;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strSkill_Q;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strSkill_E;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strSkill_R;

	TArray<FString>m_strArray;

	//
	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		ERunType m_eRunType;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32 m_iDir;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float m_fSpeed;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float m_fYaw;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool m_isFalling;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool m_isAccelerating;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_isJumpAttack;

	float m_fBeforeSpeed;

	bool m_isJumpEnable;
};