// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Fighter.generated.h"

UENUM(BlueprintType)
enum  class EFightState : uint8
{
	Idle,
	Walking,
	Hit,
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

USTRUCT(BlueprintType)
struct FHitbox {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Position;
	FHitbox(FVector Position) {
		this->Position = Position;
	}
	FHitbox() {
		this->Position = FVector::ZeroVector;
	}
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
struct UEOPENFIGHTER_API FAnimation
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UAnimationAsset* AnimatationAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FAnimFrame> Frames;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int FrameCount;
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
		FAnimation Backward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAnimation TowardsCam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAnimation AwayFromCam;
};

USTRUCT(BlueprintType)
struct UEOPENFIGHTER_API FActiveFrame
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Start;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int End;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString BoneName;
};

USTRUCT(BlueprintType)
struct UEOPENFIGHTER_API FMove
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FAnimation Animatation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FMove> Moves;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Input;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FActiveFrame> ActiveFrames;
};

USTRUCT(BlueprintType)
struct UEOPENFIGHTER_API FFighterMesh
{
	GENERATED_BODY()
	/// <summary>
	/// Bones that will get baked is hit/hurtbox
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Bones;
};

UCLASS()
class UEOPENFIGHTER_API UFighter : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FFighterMesh FighterMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMobility Mobility;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FMove> Moves;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FMove> AirMoves;
	void BakeAnim(USkeletalMeshComponent* mesh, FAnimation* anim, FMove* move);
	void BakeBones(USkeletalMeshComponent* mesh);
};

static FTransform GetWorldTransformForBone(UAnimSequence* AnimSequence, USkeletalMeshComponent* MeshComponent, const FName& InBoneName, float Seconds);