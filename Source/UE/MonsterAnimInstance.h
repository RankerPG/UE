#pragma once

#include "Info.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UCLASS()
class UE_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterAnimInstance();

public:
	FString& Get_AnimName() { return m_strCurrentAnimType; }

	void Set_AnimName(const FString& strName) { m_strCurrentAnimType = strName; }

private:
	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UFUNCTION()
	void AnimNotify_ActionToIdle();

	UFUNCTION()
	void AnimNotify_DeathEnd();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_ShotBullet();

protected:
	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_strCurrentAnimType;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_strIdle;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_strRun;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_strAttack;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_strHit;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_strDeath;

	TArray<FString> m_strArray;
};