// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter.h"


static FTransform GetWorldTransformForBone(UAnimSequence* AnimSequence, USkeletalMeshComponent* MeshComponent, const FName& InBoneName, float Seconds)
{
	FName BoneName = InBoneName;
	FTransform  WorldTransform = FTransform::Identity;

	do
	{
		int32 BoneIndex = MeshComponent->GetBoneIndex(BoneName);
		FTransform BoneTransform;
		int32 TrackIndex;

		for (TrackIndex = 0; TrackIndex < AnimSequence->GetRawTrackToSkeletonMapTable().Num(); ++TrackIndex)
		{
			if (AnimSequence->GetRawTrackToSkeletonMapTable()[TrackIndex].BoneTreeIndex == BoneIndex)
			{
				break;
			}
		}

		if (TrackIndex == AnimSequence->GetRawTrackToSkeletonMapTable().Num())
		{
			break;
		}

		AnimSequence->GetBoneTransform(BoneTransform, TrackIndex, Seconds, true);
		WorldTransform *= BoneTransform;

		BoneName = MeshComponent->GetParentBone(BoneName);
	} while (BoneName != NAME_None);

	//WorldTransform.SetToRelativeTransform(MeshComponent->GetComponentTransform());

	return WorldTransform;
}


void UFighter::BakeAnim(USkeletalMeshComponent* mesh, FAnimation* anim, FMove* move)
{
	if (anim == nullptr) return;
	auto animSeq = reinterpret_cast<UAnimSequence*>(anim->AnimatationAsset);
	auto amntFrames = FMath::CeilToInt(animSeq->SequenceLength * ANIMATION_BAKE_FPS);
	anim->FrameCount=amntFrames;
	anim->Frames.Empty();
	for (size_t i = 0; i < amntFrames; i++)
	{
		auto time = i / ANIMATION_BAKE_FPS;
		if (anim->Frames.Num() <= i)
		{
			anim->Frames.Add(FAnimFrame());
		}
		anim->Frames[i].Hurtbox.Empty();
		anim->Frames[i].Hitboxes.Empty();
		bool hitFrame = false;
		if (move != nullptr) {
			for (auto fr : move->ActiveFrames) {
				if (fr.Start < i && fr.End > i) {
					hitFrame = true;
				}
			}
		}
		for (int x = 0; x < mesh->GetNumBones(); x++)
		{
			auto boneName = mesh->GetBoneName(x);
			bool boneAvailable = false;
			for (auto cmpBone : FighterMesh.Bones) {
				auto res = cmpBone.Equals(boneName.ToString(), ESearchCase::CaseSensitive);
				boneAvailable |= res;
			}
			if (hitFrame) {
				for (auto fr : move->ActiveFrames) {
					if (fr.Start < i && fr.End > i) {
						if (fr.BoneName.Equals(boneName.ToString(), ESearchCase::CaseSensitive)) {
							auto hitloc = GetWorldTransformForBone(animSeq, mesh, boneName, time).GetLocation();
							anim->Frames[i].Hitboxes.Add(FHitbox(hitloc));
						}
					}
				}
			}
			if (!boneAvailable) continue;
			auto loc = GetWorldTransformForBone(animSeq, mesh, boneName, time).GetLocation();
			anim->Frames[i].Hurtbox.Add(FHitbox(loc));
		}

	}
}

void UFighter::BakeBones(USkeletalMeshComponent* mesh)
{
	auto mobilityAnimCount = sizeof(FMobility) / sizeof(FAnimation);
	for (size_t i = 0; i < mobilityAnimCount; i++)
	{
		BakeAnim(mesh, (FAnimation*)(&Mobility.Idle) + i, nullptr);
	}
	for (size_t i = 0; i < Moves.Num(); i++)
	{
		BakeAnim(mesh, &Moves[i].Animatation, &Moves[i]);
		printf("test?\n");
	}
	for (size_t i = 0; i < AirMoves.Num(); i++)
	{
		BakeAnim(mesh, &AirMoves[i].Animatation, &AirMoves[i]);
		printf("test?\n");
	}
}
