#include "SelectGameMode.h"
#include "CharacterDescWidget.h"

ASelectGameMode::ASelectGameMode()
{
	static ConstructorHelpers::FClassFinder<UCharacterDescWidget> DescFinder(TEXT("WidgetBlueprint'/Game/UI/BP_CharacterDescWidget.BP_CharacterDescWidget_C'"));

	if (DescFinder.Succeeded())
		m_ChracterDescWidgetClass = DescFinder.Class;
}

void ASelectGameMode::BeginPlay()
{
	if (IsValid(m_ChracterDescWidgetClass))
	{
		m_pDescWidget = CreateWidget<UCharacterDescWidget>(GetWorld(), m_ChracterDescWidgetClass);

		if (IsValid(m_pDescWidget))
			m_pDescWidget->AddToViewport();

		m_pDescWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}