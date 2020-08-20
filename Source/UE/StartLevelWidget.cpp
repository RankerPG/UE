#include "StartLevelWidget.h"
#include "Components/Button.h"

void UStartLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pStartButton = Cast<UButton>(GetWidgetFromName(TEXT("Button_Start")));
	m_pStartButton->OnClicked.AddDynamic(this, &UStartLevelWidget::Click_StartButton);

	m_pEndButton = Cast<UButton>(GetWidgetFromName(TEXT("Button_End")));
	m_pEndButton->OnClicked.AddDynamic(this, &UStartLevelWidget::Click_EndButton);
}

void UStartLevelWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStartLevelWidget::Click_StartButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLevel"));
}

void UStartLevelWidget::Click_EndButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}