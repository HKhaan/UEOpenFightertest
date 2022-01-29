#pragma once
#include "Data/Fighter.h"
#include "ECF/Component.h"
#include "Characters/UEOpenFighterCharacter.h"
#include "Misc/fpm/fixed.hpp"

extern Fix SingleFrameSpeed;
struct AnimationData{
	AnimationData()
	{
		CurrentFrame=0;
		FrameDelta = Fix(0);
		AnimSpeed = Fix(0);
		AnimationEnded=false;
		Animation = nullptr;
		AnimationEnded = false;
	}
	int CurrentFrame;
	Fix FrameDelta;
	Fix AnimSpeed;
	FAnimation* Animation;
	bool AnimationEnded;
};


class AnimationComponent: public RollbackComponent<AnimationData> {
public:
	virtual void BeginPlay(Entity* entity) override;
	virtual void Update(Entity* entity) override;
	void AnimNotify(Entity* entity,ENotifies notify);
	void PlayAnimation(FAnimation* anim, bool replayIfSame = true, Fix speed=Fix(1));
};
