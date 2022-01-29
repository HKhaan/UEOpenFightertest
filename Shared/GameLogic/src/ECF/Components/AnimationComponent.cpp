#include "AnimationComponent.h"
#include "ComponentFactory.h"
#include "FighterComponent.h"
#include "Misc/fpm/fixed.hpp"
#include "ofpch.h"
#include "BodyComponent.h"
//#include "DrawDebugHelpers.h"

Fix SingleFrameSpeed = Fix(0.1667f);
void AnimationComponent::BeginPlay(Entity* entity) {
}

void AnimationComponent::Update(Entity* entity)
{
	if(!GetData()->AnimationEnded){
		GetData()->FrameDelta += SingleFrameSpeed * GetData()->AnimSpeed;
		if (GetData()->FrameDelta >= SingleFrameSpeed) {
			GetData()->FrameDelta -= SingleFrameSpeed;
			GetData()->CurrentFrame++;
		}
		if (GetData()->CurrentFrame > GetData()->Animation->FrameCount) {
			GetData()->AnimationEnded = true;
		}
	}
}

void AnimationComponent::AnimNotify(Entity* entity, ENotifies notify)
{
	//UE_LOG(LogTemp,Warning,TEXT("Notify:%d"),(int)notify);
	//if(notify == ENotifies::Swoosh1)
	//{
	//	entity->GetData()->Channel1.Sound=entity->Actor->Swoosh1Sound;
	//	entity->GetData()->Channel1.CurrentFrame=0;
	//}
}

void AnimationComponent::PlayAnimation(FAnimation* anim, bool replayIfSame, Fix speed)
{
	if (GetData()->Animation == anim && !replayIfSame && !GetData()->AnimationEnded) return;
	GetData()->Animation = anim;
	GetData()->CurrentFrame = 0;
	GetData()->FrameDelta = Fix(0);
	GetData()->AnimSpeed = speed;
	GetData()->AnimationEnded = false;
}
