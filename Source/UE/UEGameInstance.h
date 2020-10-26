#pragma once

#include "info.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "UEGameInstance.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FItemOptionInfo
{
	GENERATED_BODY();

public:
	UPROPERTY(category = info, EditAnywhere, BlueprintReadWrite)
		EItemStatusType eType;

	UPROPERTY(category = info, EditAnywhere, BlueprintReadWrite)
		float fOption;
};

USTRUCT(Atomic, BlueprintType)
struct FGameItemInfo
{
	GENERATED_BODY();

public:
	UPROPERTY(category = info, EditAnywhere, BlueprintReadWrite)
		EItemType eType;

	UPROPERTY(category = info, EditAnywhere, BlueprintReadWrite)
		FString strName;

	UPROPERTY(category = info, EditAnywhere, BlueprintReadWrite)
		TArray<FItemOptionInfo> StatusInfoArray;
};

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

USTRUCT(BlueprintType)
struct FCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite)
		int32 Job;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite)
		float AttackPoint;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite)
		float ArmorPoint;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite)
		float AttackRange;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite)
		float HP;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite)
		float MP;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite)
		int32 Level;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite)
		int32 Exp;

	UPROPERTY(category = Status, EditAnywhere, BlueprintReadWrite)
		int32 Money;
};

struct FSaveCharacterInfo
{
public:
	EPlayerJob Job;
	float AttackPoint;
	float ArmorPoint;
	float AttackRange;
	float HPMax;
	float HP;
	float MPMax;
	float MP;
	int32 Level;
	int32 Exp;
	int32 Money;
};


UCLASS()
class UE_API UUEGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UUEGameInstance();
	~UUEGameInstance();

public:
	FSaveCharacterInfo* Get_CharacterInfo() const { return pCharacterInfo; }
	AActor* Get_Player() const { return pPlayer; }

	void Set_Player(AActor* player) { pPlayer = player; }

	UFUNCTION(BlueprintCallable)
	void Set_CharacterInfo(const FName& strName)
	{
		FCharacterInfo* pInfo = FindChracterInfo(strName);

		pCharacterInfo->Job = (EPlayerJob)pInfo->Job;
		pCharacterInfo->AttackPoint = pInfo->AttackPoint;
		pCharacterInfo->ArmorPoint = pInfo->ArmorPoint;
		pCharacterInfo->AttackRange = pInfo->AttackRange;
		pCharacterInfo->HP = pCharacterInfo->HPMax = pInfo->HP;
		pCharacterInfo->MP = pCharacterInfo->MPMax = pInfo->MP;
		pCharacterInfo->Level = pInfo->Level;
		pCharacterInfo->Exp = pInfo->Exp;
		pCharacterInfo->Money = pInfo->Money;
	}

public:
	virtual void Init();

public:
	FMonsterInfo* FindMonsterInfo(const FName& key);
	FCharacterInfo* FindChracterInfo(const FName& key);

private:
	UPROPERTY()
		UDataTable* MonsterInfoTable;

	UPROPERTY()
		UDataTable* CharacterInfoTable;

	FSaveCharacterInfo* pCharacterInfo;

	AActor* pPlayer;
};
