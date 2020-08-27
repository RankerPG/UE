#pragma once

#include "info.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
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
	void SkillR_FrozenWorld();

	void ResetPrimaryAttack();

private:
	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* m_pSpringArm;

	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* m_pCamera;

	UPROPERTY(category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* m_pMesh;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int m_iAttackCombo;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_isAttacking;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_isSaveAttack;

	UPROPERTY(category = State, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_isStun;

	class UPlayerAnimInstance* m_pAnim;

	bool m_isEvading;

	bool m_isSkillQMoving;

private: // status
	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EPlayerJob m_eJob;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fAttackPoint;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fArmorPoint;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fAttackRange;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fHP;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fHPMax;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fMP;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_fMPMax;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_iLevel;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_iExp;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_iMoney;
};