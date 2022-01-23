#include "HitComponent.h"


#include "BodyComponent.h"
#include "ComponentFactory.h"
#include "FighterComponent.h"
#include "InputReceiverComponent.h"
#include "AnimationComponent.h"
#include "WalkingComponent.h"
#include "IdleComponent.h"
#include <UEOpenFighter/Characters/UEOpenFighterCharacter.h>
class BulletComponent;


HitComponent::HitComponent()
{
}

bool HitComponent::CheckShouldTransitionTo(Entity* entity) {
	int hitInput = 0;
	hitInput |= entity->Input->JustPressed(EInputButtons::PunchButton) ? 1 : 0;
	hitInput |= entity->Input->JustPressed(EInputButtons::KickButton) ? 2 : 0;
	if (hitInput != 0) {
		auto moves = entity->FighterData->Moves;
		for (size_t i = 0; i < moves.Num(); i++)
		{
			if (moves[i].Input == hitInput) {
				entity->Animator->PlayAnimation(&(entity->FighterData->Moves[i].Animatation));
				entity->SetState(EFightState::Hit);
				return true;
			}
		}
		return false;
	}
	return false;
}

void HitComponent::Update(Entity* entity)
{
	if (!entity->Animator->GetData()->AnimationEnded) {
		return;
	}
	if (WalkingComponent::CheckShouldTransitionTo(entity)) return;
	if (IdleComponent::CheckShouldTransitionTo(entity)) return;
}
