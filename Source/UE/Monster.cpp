#include "Monster.h"
#include "MonsterAnimInstance.h"
#include "SpawnPoint.h"
#include "UEGameInstance.h"

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

void AMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FMonsterInfo* info = Cast<UUEGameInstance>(GetGameInstance())->FindMonsterInfo(*m_strMonsterName);

	if (nullptr != info)
	{
		m_fTraceRange = info->TraceRange;
		m_fAttackRange = info->AttackRange;
		m_fAttackPoint = info->AttackPoint;
		m_fArmorPoint = info->ArmorPoint;
		m_fHP = m_fMaxHP = info->HP;
		m_fMP = m_fMaxMP = info->MP;
		m_iLevel = info->Level;
		m_iExp = info->Exp;
		m_iGold = info->Gold;
	}
}

void AMonster::UnPossessed()
{
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

	FDamageEvent event;

	TakeDamage(150.f, event, GetController(), this);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Fire ball Hit"));
}

void AMonster::Death()
{

}

void AMonster::DeathEnd()
{
	Destroy();
}
