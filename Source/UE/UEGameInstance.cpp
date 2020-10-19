#include "UEGameInstance.h"

UUEGameInstance::UUEGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> TableFinder(TEXT("DataTable'/Game/Monster/MonsterInfo.MonsterInfo'"));

	if (TableFinder.Succeeded())
		MonsterInfoTable = TableFinder.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterTableFinder(TEXT("DataTable'/Game/Player/CharacterInfo.CharacterInfo'"));

	if (CharacterTableFinder.Succeeded())
		CharacterInfoTable =  CharacterTableFinder.Object;

	pCharacterInfo = new FSaveCharacterInfo;
}

UUEGameInstance::~UUEGameInstance()
{
	delete pCharacterInfo;
}

void UUEGameInstance::Init()
{
	Super::Init();

	Set_CharacterInfo(TEXT("Aurora"));
}

FMonsterInfo* UUEGameInstance::FindMonsterInfo(const FName& key)
{
	if (!IsValid(MonsterInfoTable))
		return nullptr;

	return MonsterInfoTable->FindRow<FMonsterInfo>(key, TEXT(""));
}

FCharacterInfo* UUEGameInstance::FindChracterInfo(const FName& key)
{
	if (!IsValid(CharacterInfoTable))
		return nullptr;

	return CharacterInfoTable->FindRow<FCharacterInfo>(key, TEXT(""));
}