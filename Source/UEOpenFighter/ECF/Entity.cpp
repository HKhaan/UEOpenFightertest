#include "Entity.h"
#include <UEOpenFighter/Fighters/Components/AnimationComponent.h>


Component *Entity::GetComponent(ComponentTypes componentType)  {
    if (Components.count(componentType) == 0)
        return nullptr;
    return Components.find(componentType)->second;
}

void Entity::SetState(EFightState state)
{
    Animator->Transition(this,state);
    GetData()->currentState = state;
    
    
    if (StatefullComponents.find(state) != StatefullComponents.end()) {
        StatefullComponents[state]->Update(this);
    }
}

EFightState Entity::GetState()
{
    return GetData()->currentState;
}