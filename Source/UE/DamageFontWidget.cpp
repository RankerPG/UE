#include "DamageFontWidget.h"
#include <components/Textblock.h>
#include <components/WidgetComponent.h>

void UDamageFontWidget::Set_Onwer(class UWidgetComponent* pOwner)
{
	m_pOwner = pOwner;

	if (IsValid(m_pOwner))
	{
		float fRange = (float)FMath::RandRange(-50, 50);
		m_pOwner->SetDrawSize(FVector2D(200.f, 40.f));
		m_pOwner->SetRelativeLocation(m_pOwner->GetRelativeLocation() + FVector(fRange, fRange, 150.f));
		m_vOwnerPos = m_pOwner->GetRelativeLocation();
	}
}

void UDamageFontWidget::Set_DamageText(FString strDamage)
{
	if (IsValid(m_pTextDamage))
	{
		m_pTextDamage->SetText(FText::FromString(strDamage));

		m_pTextDamage->SetVisibility(ESlateVisibility::Visible);

		if (m_VisibleTimerHander.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(m_VisibleTimerHander);

		GetWorld()->GetTimerManager().SetTimer(m_VisibleTimerHander, this, &UDamageFontWidget::UnVisible, 2.f, false);

		m_isAnimation = true;
	}
}

void UDamageFontWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pTextDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Damage")));

	m_pTextDamage->SetVisibility(ESlateVisibility::Collapsed);

	m_isAnimation = false;
}

void UDamageFontWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (true == m_isAnimation && IsValid(m_pOwner))
	{
		FVector vLoc = m_pOwner->GetRelativeLocation();
		m_pOwner->SetRelativeLocation(vLoc + FVector(0.f, 0.f, 2.f));
	}
}

void UDamageFontWidget::UnVisible()
{
	m_pTextDamage->SetVisibility(ESlateVisibility::Collapsed);

	GetWorld()->GetTimerManager().ClearTimer(m_VisibleTimerHander);

	m_isAnimation = false;

	m_pOwner->SetRelativeLocation(m_vOwnerPos);
}