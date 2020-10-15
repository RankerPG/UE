#include "Decal.h"

ADecal::ADecal()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));

	RootComponent = m_pDecal;

	m_pDecal->SetRelativeRotation(FRotator(-90.f, 90.f, 0.f));
}

void ADecal::Set_FadeTime(float fInDelay, float fInDuration, float fOutDelay, float fOutDuration)
{
	m_pDecal->SetFadeIn(fInDelay, fInDuration);

	m_pDecal->SetFadeOut(fOutDelay, fOutDuration);
}

void ADecal::Set_Attackment(USceneComponent* pComponent)
{
	m_pDecal->SetupAttachment(pComponent);
}

void ADecal::SetDecalMaterial(const FString& strPath)
{
	UMaterial* pMtrl = LoadObject<UMaterial>(nullptr, *strPath);

	m_pDecal->SetDecalMaterial(pMtrl);
}

void ADecal::BeginPlay()
{
	Super::BeginPlay();
	
}
void ADecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}