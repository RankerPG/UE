// Fill out your copyright notice in the Description page of Project Settings.


#include "UEGameInstance.h"

UUEGameInstance::UUEGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> TableFinder(TEXT("DataTable'/Game/Monster/MonsterInfo.MonsterInfo'"));

	if (TableFinder.Succeeded())
	{
		MonsterInfoTable = TableFinder.Object;
	}
}


void UUEGameInstance::Init()
{
	Super::Init();
}

FMonsterInfo* UUEGameInstance::FindMonsterInfo(const FName& key)
{
	if (!IsValid(MonsterInfoTable))
		return nullptr;

	return MonsterInfoTable->FindRow<FMonsterInfo>(key, TEXT(""));
}
