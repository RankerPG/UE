#include "SpawnPoint.h"
#include "Point.h"

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

		if (0 < m_PointArray.Num())
		{
			pMonster->Add_PatrolPos(GetActorLocation());
			pMonster->Set_PatrolEnable(true);

			for (APoint* pPoint : m_PointArray)
			{
				pMonster->Add_PatrolPos(pPoint->GetActorLocation());
			}
		}
		else
		{
			pMonster->Set_PatrolEnable(false);
		}
	}

	GetWorldTimerManager().ClearTimer(m_TimerHandler);
}

void ASpawnPoint::CallSpawnTimer()
{
	GetWorldTimerManager().SetTimer(m_TimerHandler, this, &ASpawnPoint::SpawnMonster, m_fSpawnTime, false, -1.f);
}