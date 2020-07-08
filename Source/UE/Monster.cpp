#include "Monster.h"
#include "MonsterAnimInstance.h"
#include "SpawnPoint.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMonster::CollsionHit);

	m_pAnim = nullptr;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(m_pSpawnPoint))
	{
		m_pSpawnPoint->CallSpawnTimer();
	}
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (fDamage > 0.f)
	{
		fDamage -= m_fArmorPoint;

		fDamage = fDamage <= 0.f ? 1.f : fDamage;

		m_fHP -= fDamage;

		LOG(Warning, TEXT("%f"), m_fHP);

		if (m_fHP > 0.f)
		{
			m_pAnim->Set_AnimName(TEXT("Hit"));
		}
		else
		{
			m_pAnim->Set_AnimName(TEXT("Death"));

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	return fDamage;
}

void AMonster::CollsionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	m_pAnim->Set_AnimName(TEXT("Hit"));

	LOG(Warning, TEXT("Hit!!"));
}

void AMonster::Death()
{

}

void AMonster::DeathEnd()
{
	Destroy();
}
