#pragma once

#include "EngineMinimal.h"
#include "Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(UE6, Log, All);

#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("[ Line : ") + FString::FromInt(__LINE__) + TEXT(" ]"))

#define LOG_FUNCTION(Verbosity) UE_LOG(UE6, Verbosity, TEXT("%s"), *LOG_CALLINFO);

#define LOG(Verbosity, Format, ...) UE_LOG(UE6, Verbosity, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Idle,
	Run,
	Attack,
	Death,
	Jump,
	Skill,
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	AttackNone,
	Attack1,
	Attack2,
	Attack3,
	Attack4
};

UENUM(BlueprintType)
enum class EJumpType : uint8
{
	JumpNone,
	JumpStart,
	JumpLoop,
	Landing,
	Recover
};

UENUM(BlueprintType)
enum ECollisionChannelConvert
{
	CollisionNone,
	CollisionPlayer = ECC_GameTraceChannel1,
	CollisionMonster,
	CollisionPlayerAttack,
	Collsion4,
	Collsion5,
	Collsion6,
	Collsion7,
	Collsion8,
	Collsion9,
	Collsion10,
};