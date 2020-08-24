#include "PlayerStatusWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "UEGameInstance.h"

void UPlayerStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pPlayerImage = Cast<UImage>(GetWidgetFromName(TEXT("Image_Player")));
	m_pTextName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name")));
	m_pTextLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Level")));
	m_pTextAttack = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Attack")));
	m_pTextArmor = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Armor")));
	m_pTextAttackRange = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_AttackRange")));
	m_pTextHP = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_HP")));
	m_pTextMP = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_MP")));

	UUEGameInstance* pInstance = Cast<UUEGameInstance>(GetGameInstance());
	FSaveCharacterInfo* pInfo = pInstance->Get_CharacterInfo();

	FString strName;
	strName = pInfo->Job == EPlayerJob::KNINGHT ? TEXT("Aurora") : TEXT("X");
	m_pTextName->SetText(FText::FromString(strName));
	
	FString strLevel = FString::Printf(TEXT("Level : %d"), pInfo->Level);
	m_pTextLevel->SetText(FText::FromString(strLevel));

	FString strAttack = FString::Printf(TEXT("Attack Point : %.1f"), pInfo->AttackPoint);
	m_pTextAttack->SetText(FText::FromString(strAttack));

	FString strArmor = FString::Printf(TEXT("Armor Point : %.1f"), pInfo->ArmorPoint);
	m_pTextArmor->SetText(FText::FromString(strArmor));

	FString strAttackRange = FString::Printf(TEXT("Attack Range : %.1f"), pInfo->AttackRange);
	m_pTextAttackRange->SetText(FText::FromString(strAttackRange));

	FString strHP = FString::Printf(TEXT("HP : %.0f / %.0f"), pInfo->HP, pInfo->HPMax);
	m_pTextHP->SetText(FText::FromString(strHP));

	FString strMP = FString::Printf(TEXT("MP : %.0f / %.0f"), pInfo->MP, pInfo->MPMax);
	m_pTextMP->SetText(FText::FromString(strMP));

}

void UPlayerStatusWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}