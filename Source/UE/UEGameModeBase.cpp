#include "UEGameModeBase.h"
#include "MainWidget.h"

AUEGameModeBase::AUEGameModeBase()
{
	ConstructorHelpers::FClassFinder<UMainWidget>  MainWidgetFinder(TEXT("WidgetBlueprint'/Game/UI/BP_MainWidget.BP_MainWidget_C'"));

	if (MainWidgetFinder.Succeeded())
		m_MainWidgetClass = MainWidgetFinder.Class;
}

void AUEGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_MainWidgetClass))
	{
		m_pMainWidget = Cast<UMainWidget>(CreateWidget<UMainWidget>(GetWorld(), m_MainWidgetClass));

		if (IsValid(m_pMainWidget))
			m_pMainWidget->AddToViewport();

		m_pMainWidget->SetRenderTranslation(FVector2D(0.f, 0.f));
	}
}