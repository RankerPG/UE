#pragma once

#include "Info.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate)

UCLASS()
class UE_API AMonster : public ACharacter
{
	GENERATED_BODY()

private:
	friend class ASpawnPoint;

public:
	AMonster();

public:
	FString& Get_AnimSequence();
	float Get_TraceRange() { return m_fTraceRange; }
	float Get_AttackRange() { return m_fAttackRange; }
	float Get_HP() { return m_fHP; }
	int32 Get_PatrolNum() { return m_iPatrolNum; }
	const FVector& Get_PatrolPos() { return m_PatrolPosArray[m_iPatrolNum]; }
	const FVector& Get_NextPatrolPos();
	bool Get_PatrolEnable() { return m_bPatrolEnable; }

	void Set_AnimSequence(const FString& strAnim);
	void Set_PatrolEnable(bool bPatrolEnable) { m_bPatrolEnable = bPatrolEnable; }
	UFUNCTION(BlueprintCallable)
	void Add_PatrolPos(const FVector& vPos) { m_PatrolPosArray.Add(vPos); }

public:
	template <typename T>
	void Add_AttackEndFunction(T* pObj, void(T::* func)(void))
	{
		FDelegateHandle handle = m_OnAttackEnd.AddUObject(pObj, func);
		
		m_AttackEndHandleArray.Add(handle);
	}

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION()
	virtual void CollsionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void Death();
	virtual void DeathEnd();

public:
	void AttackEnd();

	bool CollisionCheck(FHitResult& resultOut);

protected:
	UPROPERTY(category = Monster, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ASpawnPoint* m_pSpawnPoint;

	class UMonsterAnimInstance* m_pAnim;

	class AMinionAIController* m_pController;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FVector> m_PatrolPosArray;

	FOnAttackEndDelegate m_OnAttackEnd;
	TArray<FDelegateHandle> m_AttackEndHandleArray;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 m_iPatrolNum;

	bool m_bPatrolEnable;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_strMonsterName;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fTraceRange;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fAttackRange;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fAttackDelay;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fAttackPoint;
	
	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fArmorPoint;
	
	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fHP;
	
	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fMaxHP;
	
	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fMP;
	
	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_fMaxMP;
	
	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int m_iLevel;
	
	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int m_iExp;
	
	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int m_iGold;
};
