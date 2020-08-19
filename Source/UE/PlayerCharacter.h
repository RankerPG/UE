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
	void Action_DropWeapon();
	void Action_Skill_1();
	void Action_Dash();

public:
	void Fireball();
	bool CollisionCheck(TArray<FHitResult>& resultOut);
	void Move_Dash();
	void Dash_End();

private:
	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* m_pSpringArm;

	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* m_pCamera;

	UPROPERTY(category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* m_pMesh;

	class UPlayerAnimInstance* m_pAnim;

	class AWeapon* m_pWeapon;

	UClass* m_pWeaponClass;

	FRotator m_rotDash;

	float m_fAttackRange;

	float m_fAttackPoint;
};