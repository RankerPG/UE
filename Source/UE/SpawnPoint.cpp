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

	CreateMonster();
}

void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnPoint::CreateMonster()
{
	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	m_pMonster = Cast<AMonster>(GetWorld()->SpawnActor(m_MonsterClass, &vLoc, &vRot, tParams));

	if (IsValid(m_pMonster))
	{
		m_pMonster->m_pSpawnPoint = this;

		if (0 < m_PointArray.Num())
		{
			m_pMonster->Add_PatrolPos(GetActorLocation());
			m_pMonster->Set_PatrolEnable(true);

			for (APoint* pPoint : m_PointArray)
			{
				m_pMonster->Add_PatrolPos(pPoint->GetActorLocation());
			}
		}
		else
		{
			m_pMonster->Set_PatrolEnable(false);
		}
	}

	GetWorldTimerManager().ClearTimer(m_TimerHandler);
}

void ASpawnPoint::SpawnMonster()
{
	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();

	if (IsValid(m_pMonster))
	{
		m_pMonster->SetActorLocationAndRotation(vLoc, vRot);
		m_pMonster->SpawnSetting();
	}

	GetWorldTimerManager().ClearTimer(m_TimerHandler);
}

void ASpawnPoint::CallSpawnTimer()
{
	GetWorldTimerManager().SetTimer(m_TimerHandler, this, &ASpawnPoint::SpawnMonster, m_fSpawnTime, false, -1.f);
}