#include "StartGameMode.h"
#include "UIPlayerController.h"
#include "StartLevelWidget.h"

AStartGameMode::AStartGameMode()
{
	PlayerControllerClass = AUIPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<UStartLevelWidget> startLevelWidgetClass(TEXT("WidgetBlueprint'/Game/UI/BP_StartWidget.BP_StartWidget_C'"));

	if (startLevelWidgetClass.Succeeded())
		m_StartLevelWidgetClass = startLevelWidgetClass.Class;
}

void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_StartLevelWidgetClass))
	{
		m_pStartLevelWidget = Cast<UStartLevelWidget>(CreateWidget(GetWorld(), m_StartLevelWidgetClass));

		if (nullptr != m_pStartLevelWidget)
			m_pStartLevelWidget->AddToViewport();

		m_pStartLevelWidget->SetRenderTranslation(FVector2D(0.f, 0.f));
	}
}