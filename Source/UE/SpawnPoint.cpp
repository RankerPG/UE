#include "SpawnPoint.h"

ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	m_fSpawnTime = 3.f;
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	SpawnMonster();
}

void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPoint::SpawnMonster()
{
	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AMonster* pMonster = Cast<AMonster>(GetWorld()->SpawnActor(m_MonsterClass, &vLoc, &vRot, tParams));

	if (IsValid(pMonster))
	{
		pMonster->m_pSpawnPoint = this;
	}

	GetWorldTimerManager().ClearTimer(m_TimerHandler);
}

void ASpawnPoint::CallSpawnTimer()
{
	GetWorldTimerManager().SetTimer(m_TimerHandler, this, &ASpawnPoint::SpawnMonster, m_fSpawnTime, false, -1.f);
}