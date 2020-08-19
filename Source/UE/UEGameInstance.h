// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "info.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "UEGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(category = Data, EditAnywhere, BlueprintReadWrite)
	float TraceRange;

	UPROPERTY(category = Data, EditAnywhere, BlueprintReadWrite)
	float AttackRange;

	UPROPERTY(category = Data, EditAnywhere, BlueprintReadWrite)
	float AttackDelay;

	UPROPERTY(category = Data, EditAnywhere, BlueprintReadWrite)
	float AttackPoint;

	UPROPERTY(category = Data, EditAnywhere, BlueprintReadWrite)
	float ArmorPoint;

	UPROPERTY(category = Data, EditAnywhere, BlueprintReadWrite)
	float HP;

	UPROPERTY(category = Data, EditAnywhere, BlueprintReadWrite)
	float MP;

	UPROPERTY(category = Data, EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(category = Data, EditAnywhere, BlueprintReadWrite)
	int32 Exp;

	UPROPERTY(category = Data, EditAnywhere, BlueprintReadWrite)
	int32 Gold;
};


UCLASS()
class UE_API UUEGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UUEGameInstance();

private:
	UPROPERTY()
	UDataTable* MonsterInfoTable;

public:
	virtual void Init();

public:
	FMonsterInfo* FindMonsterInfo(const FName& key);
	
};
