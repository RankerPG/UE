#pragma once

#include "info.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//Axis
	void Move_Foward(float fScale);
	void Move_Side(float fScale);
	void Mouse_X(float fScale);
	void Mouse_Y(float fScale);
	void Mouse_Wheel(float fScale);

	//Action
	void Action_Jump();
	void Action_Attack();
	void Drop_Weapon();
	void Skill_1();

public:
	void Fireball();

private:
	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent*	m_pSpringArm;

	UPROPERTY(category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent*		m_pCamera;

	class UPlayerAnimInstance* m_pAnim;

	class AWeapon* m_pWeapon;

	UClass* m_pWeaponClass;

	float m_fAttackRange;

	float m_fAttackPoint;
};
