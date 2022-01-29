#include "IdleComponent.h"
#include "WalkingComponent.h"
#include "HitComponent.h"
#include "AnimationComponent.h"
#include "InputReceiverComponent.h"
#include "ofpch.h"
bool IdleComponent::CheckShouldTransitionTo(Entity* entity)
{
	
	if (entity->Input->GetData()->Input == 0 && entity->Animator->GetData()->AnimationEnded) {
		entity->SetState(EFightState::Idle);
		return true;
	}
	return false;
}




void IdleComponent::Update(Entity* entity)
{
	if (HitComponent::CheckShouldTransitionTo(entity)) return;
	if(WalkingComponent::CheckShouldTransitionTo(entity)) return;
	entity->Animator->PlayAnimation(&entity->FighterData->Mobility.Idle, false);
}
