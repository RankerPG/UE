#pragma once

#include "Info.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate)

UCLASS(Blueprintable, BlueprintType)
class UE_API AMonster : public ACharacter
{
	GENERATED_BODY()

private:
	friend class ASpawnPoint;

public:
	AMonster();

public:
	FString Get_AnimType();
	const FVector& Get_PatrolPos() { return m_PatrolPosArray[m_iPatrolNum]; }
	const FVector& Get_NextPatrolPos();
	ECharacterState Get_State();
	int32 Get_PatrolNum() { return m_iPatrolNum; }
	float Get_TraceRange() { return m_fTraceRange; }
	float Get_AttackRange() { return m_fAttackRange; }
	UFUNCTION(BlueprintCallable)
		float Get_HP() { return m_fHP; }
	bool Get_AttackEnable() { return m_isAttackEnable; }
	bool Get_PatrolEnable() { return m_isPatrolEnable; }

	UFUNCTION(BlueprintCallable)
		void Add_PatrolPos(const FVector& vPos) { m_PatrolPosArray.Add(vPos); }
	void Set_AnimType(const FString& strAnim);
	void Set_PatrolEnable(bool isPatrolEnable) { m_isPatrolEnable = isPatrolEnable; }
	void Set_AttackEnable(bool isAttackEnable) { m_isAttackEnable = isAttackEnable; }
	UFUNCTION(BlueprintCallable)
		void Set_Frozen(float fFrozenTime);
	UFUNCTION(BlueprintCallable)
		void Set_Stun(float fStunTime);
	UFUNCTION(BlueprintCallable)
	void Set_Knockback(float fKnockbackTime);

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

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	void SpawnSetting();
	void DeathEnd();

public:
	void AttackDelay();
	void AttackEnd();

	bool CollisionCheck(FHitResult& resultOut);

protected:
	UPROPERTY(category = Monster, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class ASpawnPoint* m_pSpawnPoint;

	UPROPERTY(category = Mesh, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* m_pMesh;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<FVector> m_PatrolPosArray;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_iPatrolNum;

	UPROPERTY(category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<class UWidgetComponent*> m_arrFont;

	UPROPERTY(category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* m_pMonsterInfoHUDWidget;

	class AMinionAIController* m_pController;

	class UMonsterAnimInstance* m_pAnim;

	FOnAttackEndDelegate m_OnAttackEnd;
	TArray<FDelegateHandle> m_AttackEndHandleArray;

	FTimerHandle m_AttackDelayTimerHandle;

	int m_iFontIndex;

	bool m_isPatrolEnable;

	bool m_isAttackEnable;

protected: // status
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
		float m_fHPMax;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fMP;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fMPMax;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int m_iLevel;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int m_iExp;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int m_iGold;
};
