#pragma once

class UAnimationAsset {
	void* asset;
};

enum  class EFightState : uint8
{
	Idle,
	Walking,
	Hit,
	GotHit,
};

enum  class ENotifies : uint8
{
	None,
	Swoosh1,
	Swoosh2,
	Footstep1,
	Footstep2
};

struct FHitbox {
	FVector Position;
	FHitbox(FVector Position) {
		this->Position = Position;
	}
	FHitbox() {
		this->Position = FVector::ZeroVector;
	}
};

struct FAnimFrame
{
		std::vector<FHitbox> Hitboxes;
		std::vector<FHitbox> Hurtbox;
		ENotifies Notify;
};

struct FAnimation
{
		UAnimationAsset* AnimatationAsset;
		std::vector<FAnimFrame> Frames;
		int FrameCount;
};

struct FMobility
{
		FAnimation Idle;
		FAnimation Forward;
		FAnimation Backward;
		FAnimation TowardsCam;
		FAnimation AwayFromCam;
};

struct FActiveFrame
{
		int Start;
		int End;
		FString BoneName;
};

struct FMove
{
		FAnimation Animatation;
		std::vector<FMove> Moves;
		int Input;
		std::vector<FActiveFrame> ActiveFrames;
};

struct FFighterMesh
{
	TArray<FString> Bones;
};

class UFighter : public UDataAsset
{
public:
		std::string Name;
		FFighterMesh FighterMesh;
		FMobility Mobility;
		TArray<FMove> Moves;
		TArray<FMove> AirMoves;
};
