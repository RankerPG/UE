#pragma once

#include "info.h"
#include "Animation/AnimInstance.h"
#include "SuperAnimInstance.generated.h"

UCLASS()
class UE_API USuperAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USuperAnimInstance();

public:
	//Get
	FString Get_AnimType() { return m_strCurrentAnimType; }
	ECharacterState Get_State() { return m_eState; }

	//Set
	void Set_AnimType(const FString& strName) { m_strCurrentAnimType = strName; }
	void Set_State(ECharacterState eState) { m_eState = eState; }
	void Set_Frozen(float fFrozenTime);
	void Set_Stun(float fStunTime);
	void Set_Knockback(float fKnockbackTime);

protected:
	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UFUNCTION()
		void AnimNotify_ActionToIdle();

	// 100 = 1.f;
	UFUNCTION()
		void AnimNotify_ChangePlayRate_100();

	UFUNCTION()
		void AnimNotify_ChangePlayRate_200();

protected:
	bool DeathCheck();

	void FrozenEnd();
	void StunEnd();
	void KnockbackEnd();

protected:
	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_strCurrentAnimType;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		ECharacterState m_eState;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float m_fPlayRate;

	TArray<FString> m_strArray;

	FTimerHandle m_FrozenTimerHandle;
	FTimerHandle m_StunTimerHandle;
	FTimerHandle m_KnockbackTimerHandle;

	ACharacter* m_pCharacter; // 캐릭터용 함수를 사용하기 위해서 가지고 있지만 자식의 경우 그에 맞는 캐릭터의 형변환 값을 가지도록 한다.
};
