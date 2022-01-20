#pragma once
#include "UEOpenFighter/Data/Fighters.h"
#include "UEOpenFighter/ECF/Component.h"
#include <UEOpenFighter/Characters/UEOpenFighterCharacter.h>

struct AnimationData{
	AnimationData()
	{
		CurrentFrame=0;
		AnimationEnded=false;
		Animation = nullptr;
		InTransition = false;
	}
	int CurrentFrame;
	FAnimation* Animation;
	bool AnimationEnded;
	bool InTransition;
};


class AnimationComponent: public RollbackComponent<AnimationData> {
public:
	void Transition(Entity* entity, EFightState nextState);
	bool InTransition() { return GetData()->InTransition; }
	virtual void BeginPlay(Entity* entity) override;
	virtual void Update(Entity* entity) override;
	void AnimNotify(Entity* entity,ENotifies notify);
};
