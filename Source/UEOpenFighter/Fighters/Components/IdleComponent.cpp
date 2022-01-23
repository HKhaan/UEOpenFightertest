#include "IdleComponent.h"
#include "WalkingComponent.h"
#include "HitComponent.h"
#include "AnimationComponent.h"
#include "InputReceiverComponent.h"
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
	if(entity->Input&& entity->Input->GetData()->AssignedGamepad<0)
	{
		UE_LOG(LogTemp,Warning,TEXT("test"));
	}
	entity->Animator->GetData()->Animation = &entity->FighterData->Mobility.Idle;
	WalkingComponent::CheckShouldTransitionTo(entity);
	if (HitComponent::CheckShouldTransitionTo(entity)) return;
}
