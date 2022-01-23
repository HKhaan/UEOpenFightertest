#include "HitboxComponent.h"

#include "FighterComponent.h"
#include "AnimationComponent.h"
#include "BodyComponent.h"
#include "ComponentFactory.h"
#include "UEOpenFighter/ECF/World.h"

void HitboxComponent::Update(Entity* entity)
{
	//TODO: refactor needed;
	if (entity->GetState() == EFightState::Hit) {
		auto animator = (AnimationComponent*)entity->GetComponent(ComponentTypes::AnimationComponentType);

	}
}
