#pragma once
#include "UEOpenFighter/ECF/Entity.h"

#include "ComponentTypes.h"


class ComponentFactory {
public:
    static Component* AddComponent(Entity* entity, ComponentTypes type);
};


