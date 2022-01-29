#pragma once
#include <vector>
#include <list>
#include <functional>
#include <UEOpenFighter/Fighters/Components/ComponentTypes.h>

class Entity;
class World {
public:
    static std::list<Entity*> entities;
    static Entity* CreateEntity();
    static void Update();
    static void Destroy();
    static std::list<ComponentTypes> componentTypes;
    static int PhysicsPrecision;
    static void TickPhysics();
    static void TickInputs();
};

