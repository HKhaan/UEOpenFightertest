// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Fighters.generated.h"

UENUM(BlueprintType)
enum  class EFightState : uint8
{
	Idle,
	Walking,
	Kick,
	Punch,
	GotHit,
};

UENUM(BlueprintType)
enum  class ENotifies : uint8
{
	None,
	Swoosh1,
	Swoosh2,
	Footstep1,
	Footstep2
};

//
// UENUM()
// enum  EComparison
// {
// 	Equal,
// 	GT,
// 	LT
// };

USTRUCT(BlueprintType)
struct UEOPENFIGHTER_API FComparator
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EFightState State;
};

USTRUCT(BlueprintType)
struct FHitbox {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int RefHeight;
};

USTRUCT(BlueprintType)
struct FHitboxPercentage {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Width;

};
USTRUCT(BlueprintType)
struct FAnimFrame
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FHitbox> Hitboxes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FHitbox> Hurtbox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ENotifies Notify;
};
USTRUCT(BlueprintType)
struct FAnimTransition
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USkeletalMesh* Flipbook;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EFightState State;
};

USTRUCT(BlueprintType)
struct UEOPENFIGHTER_API FAnimation
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PauseAfterAnimationEnded;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UAnimationAsset* AnimatationAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector2D EditorPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FAnimFrame> Frames;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EFightState State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAnimTransition> Transitions;
};

USTRUCT(BlueprintType)
struct UEOPENFIGHTER_API FMobility
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAnimation Idle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAnimation Forward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAnimation Crouch;
};

USTRUCT(BlueprintType)
struct UEOPENFIGHTER_API FFighter
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMobility Mobility;

};

