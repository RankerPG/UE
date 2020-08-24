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
	void Set_Attacking(bool isAttacking) { m_isAttacking = isAttacking; }
	void Set_Evading(bool isEvading) { m_isEvading = isEvading; }

	int Get_AttackCombo() const { return m_iAttackCombo; }
	bool Get_Evading() const { return m_isEvading; }

protected:
	virtual void BeginPlay() override;

public:
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
	void Action_Skill_1();
	void Action_Evade();

public:
	void Fireball();
	bool CollisionCheck(TArray<FHitResult>& resultOut);
	void Evade_Move();

	void ResetPrimaryAttack();

private:
	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_pSpringArm;

	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_pCamera;

	UPROPERTY(category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* m_pMesh;

	class UPlayerAnimInstance* m_pAnim;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int m_iAttackCombo;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_isAttacking;

	UPROPERTY(category = Attack, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_isSaveAttack;

	bool m_isEvading;

private:
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