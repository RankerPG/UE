#include "Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = m_pMesh;

	m_pMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Drop()
{
	m_pMesh->SetSimulatePhysics(true);
}

void AWeapon::Load_Weapon(const FString& strPath)
{
	UStaticMesh* pMesh = LoadObject<UStaticMesh>(nullptr, *strPath, nullptr, LOAD_None);

	if (IsValid(pMesh))
	{
		m_pMesh->SetStaticMesh(pMesh);
	}
}