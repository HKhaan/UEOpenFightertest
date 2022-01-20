#include "KickComponent.h"


#include "BodyComponent.h"
#include "ComponentFactory.h"
#include "FighterComponent.h"
#include "InputReceiverComponent.h"
#include "AnimationComponent.h"
#include "WalkingComponent.h"
#include "IdleComponent.h"
#include <UEOpenFighter/Characters/UEOpenFighterCharacter.h>
class BulletComponent;


KickComponent::KickComponent()
{
}

bool KickComponent::CheckShouldTransitionTo(Entity* entity) {
	if (entity->Input->JustPressed(EInputButtons::KickButton)) {
		entity->SetState(EFightState::Kick);
		
		return true;
	}
	return false;
}

void KickComponent::Update(Entity* entity)
{
	if (WalkingComponent::CheckShouldTransitionTo(entity)) return;
	if (IdleComponent::CheckShouldTransitionTo(entity)) return;
	if (entity->Animator->InTransition()) {
	
	}
	else {
	}
}
