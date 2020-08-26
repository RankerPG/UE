#pragma once

#include "SuperAnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UCLASS()
class UE_API UMonsterAnimInstance : public USuperAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterAnimInstance();

protected:
	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UFUNCTION()
		void AnimNotify_DeathEnd();

	UFUNCTION()
		void AnimNotify_AttackEnd();

	UFUNCTION()
		void AnimNotify_ShotBullet();

	UFUNCTION()
		void AnimNotify_CollisionCheck();

private:
	class AMonster* m_pMonster;

protected:
	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_strIdle;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_strPatrol;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_strRun;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_strAttack;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_strHit;

	UPROPERTY(category = AnimType, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_strDeath;
};