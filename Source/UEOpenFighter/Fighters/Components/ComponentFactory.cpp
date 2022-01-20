#include "ComponentFactory.h"
#include "InputReceiverComponent.h"
#include <map>


#include "AnimationComponent.h"
#include "BodyComponent.h"
#include "KickComponent.h"
#include "WalkingComponent.h"
#include "IdleComponent.h"
#include "HitboxComponent.h"
#include "FighterComponent.h"
#include "UEOpenFighter/ECF/World.h"
//#include <algorithm>

#define DEFINE_STATELESS_COMPONENT(type,component)\
	case type :\
        {\
        	comp = new component ();\
			comp->BeginPlay(entity);\
        	entity->Components[type] = comp;\
        	entity->StatelessComponents[type] = comp;\
        	break;\
        }

#define DEFINE_STATEFULL_COMPONENT(type,state,component)\
	case type :\
        {\
        	comp = new component ();\
			comp->BeginPlay(entity);\
        	entity->Components[type] = comp;\
			entity->StatefullComponents[state] = comp;\
        	break;\
        }


Component* ComponentFactory::AddComponent(Entity* entity, ComponentTypes type)
{
	Component* comp=nullptr;
	//TODO: check if already exists
	switch (type)
	{
		DEFINE_STATELESS_COMPONENT(ComponentTypes::InputReceiverComponentType,InputReceiverComponent)
		DEFINE_STATELESS_COMPONENT(ComponentTypes::BodyComponentType,BodyComponent)
		DEFINE_STATELESS_COMPONENT(ComponentTypes::AnimationComponentType,AnimationComponent)
		DEFINE_STATELESS_COMPONENT(ComponentTypes::HitboxComponentType, HitboxComponent)
		DEFINE_STATEFULL_COMPONENT(ComponentTypes::WalkingComponentType,EFightState::Walking,WalkingComponent)
		DEFINE_STATEFULL_COMPONENT(ComponentTypes::KickComponentTypes, EFightState::Kick,KickComponent)
		DEFINE_STATEFULL_COMPONENT(ComponentTypes::IdleComponentType, EFightState::Idle, IdleComponent)
			//DEFINE_STATELESS_COMPONENT(ComponentTypes::FighterComponentType,FighterComponent)
	default:
		break;
	}
	if (!(std::find(World::componentTypes.begin(), World::componentTypes.end(), type) !=
		World::componentTypes.end()))
		World::componentTypes.push_back(type);
	return comp;
	//std::sort(World::componentTypes.begin(), World::componentTypes.end());
}
