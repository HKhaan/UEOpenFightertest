#include "AnimationComponent.h"
#include "ComponentFactory.h"
#include "FighterComponent.h"
#include <UEOpenFighter/Misc/fpm/fixed.hpp>

#include "BodyComponent.h"
#include "DrawDebugHelpers.h"

void AnimationComponent::Transition(Entity* entity,EFightState nextState)
{
	//auto fighter = (FighterComponent*)entity->GetComponent(ComponentTypes::FighterComponentType);
	//for(auto anim: entity->FighterData->Animations)
	//{
	//	if(anim.State == entity->GetState())
	//	{
	//		if(GetData()->AnimationId != anim.Id){
	//			GetData()->AnimationId =anim.Id;
	//			GetData()->Flipbook = anim.Flipbook;
	//			GetData()->AnimationEnded = false;
	//			GetData()->CurrentFrame=0;
	//			GetData()->InTransition = false;
	//			return;
	//		}
	//		for(auto trans: anim.Transitions)
	//		{
	//			if(trans.State==nextState)
	//			{
	//				GetData()->AnimationId =anim.Id;
	//				GetData()->Flipbook = trans.Flipbook;
	//				GetData()->InTransition = true;
	//				return;
	//			}
	//		}
	//	}
	//}
}

void AnimationComponent::BeginPlay(Entity* entity) {
	//GetData()->Flipbook = entity->FighterData->Animations[0].Flipbook;
	//GetData()->AnimationId= 1;//entity->FighterData->Animations[0];
	//
	//entity->Actor->GetSprite()->SetFlipbook(entity->FighterData->Animations[0].Flipbook);
	//entity->Actor->GetSprite()->Stop();
}

void AnimationComponent::Update(Entity* entity)
{
	//UPaperFlipbookComponent* FlipbookComponent = entity->Actor->GetSprite();
	//UPaperFlipbook* ThisFlipbook = FlipbookComponent->GetFlipbook();
	//auto FramesToSeconds = (Fix)GetData()->Flipbook->GetTotalDuration();
	//auto AnimationLastTick = FramesToSeconds * (Fix)GAMESPEED_FPS - 1;

	//if(!GetData()->AnimationEnded)
	//{
	//	GetData()->CurrentFrame++; // resets when animation loops
	//}

	//// playhead of the current flipbook in seconds
	//auto Head = (fixed_8_24)GetData()->CurrentFrame / (fixed_8_24)GAMESPEED_FPS;
	//entity->Actor->CurrentFrame=GetData()->CurrentFrame ;
	//GetData()->AnimationEnded = GetData()->CurrentFrame >= (int)AnimationLastTick;
	//for(auto anim: entity->FighterData->Animations)
	//{
	//	if(anim.Id==GetData()->AnimationId )
	//	{
	//		if(anim.Frames.Num()>GetData()->CurrentFrame && anim.Frames[GetData()->CurrentFrame].Notify!=ENotifies::None)
	//		{
	//			AnimNotify(entity,anim.Frames[GetData()->CurrentFrame].Notify);
	//		}
	//	}
	//}
	////TODO: check if transition is done instead of flagging it as false
	//if(GetData()->InTransition)
	//{
	//	if(GetData()->AnimationEnded){
	//		GetData()->InTransition	=true;
	//		Transition(entity,entity->GetState());
	//	}
	//}else{
	//	Transition(entity,entity->GetState());
	//}
	//if(GetData()->AnimationEnded)
	//{
	//	// if(!GetData()->Animation.PauseAfterAnimationEnded)
	//	// {
	//	// 	GetData()->CurrentFrame = 0;
	//	// }
	//}
	//
	//if(ThisFlipbook != GetData()->Flipbook)
	//{
	//	FlipbookComponent->SetFlipbook(GetData()->Flipbook);
	//	FlipbookComponent->Stop();
	//}
	//
	//FlipbookComponent->SetPlaybackPosition((float)Head, true);
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
