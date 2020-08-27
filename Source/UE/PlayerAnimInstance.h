#pragma once

#include "SuperAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class UE_API UPlayerAnimInstance : public USuperAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

public:
	ERunType Get_RunType() { return m_eRunType; }
	bool Get_JumpEnable() { return m_isJumpEnable; }

	void Set_RunType(ERunType eRunType) { m_eRunType = eRunType; }
	void Add_Yaw(float fDirection);

protected:
	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UFUNCTION()
		void AnimNotify_AttackEnable();

	UFUNCTION()
		void AnimNotify_JumpEntry();

	UFUNCTION()
		void AnimNotify_JumpToIdle();

	UFUNCTION()
		void AnimNotify_JumpEnd();

	UFUNCTION()
		void AnimNotify_Fireball();

	UFUNCTION()
		void AnimNotify_CollisionCheck();

	UFUNCTION()
		void AnimNotify_CollisionCheck_Sphere();

	UFUNCTION()
		void AnimNotify_EvadeEnd();

	UFUNCTION()
		void AnimNotify_AttackToDash();

	UFUNCTION()
		void AnimNotify_SkillQMovingOnOff();

protected:
	class APlayerCharacter* m_pPlayer;

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
		FString m_strEvade;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strSkill_Q;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strSkill_E;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FString m_strSkill_R;

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