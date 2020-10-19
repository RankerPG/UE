#pragma once

#include "info.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

public:
	ECharacterState Get_State();
	int Get_AttackCombo() const { return m_iAttackCombo; }
	bool Get_Evading() const { return m_isEvading; }

	void Set_Evading(bool isEvading) { m_isEvading = isEvading; }
	void Set_SkillQMoving() { m_isSkillQMoving ^= true; }
	void Set_Frozen(float fFrozenTime);
	void Set_Stun(float fStunTime);
	void Update_HP(float fScale);
	void Update_MP(float fScale);
	void Recover_MP();
	void Reset_AttackInfo();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	//Axis
	void Move_Forward(float fScale);
	void Move_Side(float fScale);
	void Mouse_X(float fScale);
	void Mouse_Y(float fScale);
	void Mouse_Wheel(float fScale);

	//Action
	void Action_Jump();
	void Action_Attack();
	void Action_Skill_Q();
	void Action_Skill_E();
	void Action_Skill_R();
	void Action_Evade();
	void Action_MouseEnable();

public:
	void Fireball();
	bool CollisionCheck(TArray<FHitResult>& resultOut);
	bool CollisionCheck_Sphere(TArray<FHitResult>& resultOut);
	bool CollisionCheck_Knockback(TArray<FHitResult>& resultOut);
	void Evade_Move();
	void SkillQ_Move();
	void SkillE_SpikeCircle();
	void SkillR_FrozenWorld();

	void ResetPrimaryAttack();

private:
	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* m_pSpringArm;

	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* m_pCamera;

	UPROPERTY(category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* m_pMesh;

	UPROPERTY(category = UI, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* m_pCharacterInfoHUDWidget;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int m_iAttackCombo;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_isAttacking;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_isSaveAttack;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_isStun;

	class UPlayerAnimInstance* m_pAnim;

	TSubclassOf<class AIceSpike> m_pSpike;

	FTimerHandle m_RecoverMPHandle;

	bool m_isEvading;

	bool m_isSkillQMoving;

private: // Status
	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_strName;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EPlayerJob m_eJob;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fAttackPoint;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fArmorPoint;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fAttackRange;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fHP;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fHPMax;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fMP;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fMPMax;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_iLevel;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_iExp;

	UPROPERTY(category = Status, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_iMoney;

	float m_fSkillQDamagePoint;
	float m_fSkillEDamagePoint;
	float m_fSkillRDamagePoint;
};