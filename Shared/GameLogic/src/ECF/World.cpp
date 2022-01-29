#include "World.h"
#include "Entity.h"
#include "Component.h"
#include <map>

#include "ECF/Components/BodyComponent.h"
#include "ECF/Components/InputReceiverComponent.h"
#include "ofpch.h"
std::list<Entity*> World::entities;
std::list<ComponentTypes> World::componentTypes;
int World::PhysicsPrecision = 2;
Entity* World::CreateEntity() {
    auto entity = new Entity();
    entity->GetData()->active=true;
    entities.push_back(entity);
    return entity;
}

void World::Update()  {
    //TODO: take this out of StatelessComonents
    for (auto ent = entities.begin(); ent != entities.end(); ent++)
    {
        if((*ent)->Input && (*ent)->Input->GetData()->AssignedGamepad<0)
        {
            (*ent)->Input->Update((*ent));
        }
    }
    for (auto comp = componentTypes.begin(); comp != componentTypes.end(); comp++)
    {
        for (auto ent = entities.begin(); ent != entities.end(); ent++) {
            if(!(*ent)->GetData()->active) continue;
            auto component = (*ent)->GetComponent(*comp);
            if((*ent)->Input && (*ent)->Input->GetData()->AssignedGamepad<0)
            {
                UE_LOG(LogTemp,Warning,TEXT("??????"));
            }
            if ((*ent)->StatelessComponents.find((*comp)) != (*ent)->StatelessComponents.end()) {
                (*ent)->StatelessComponents[(*comp)]->Update(*ent);
            }
        }
    }
    for (auto ent = entities.begin(); ent != entities.end(); ent++) {
        if(!(*ent)->GetData()->active) continue;
        if((*ent)->Input && (*ent)->Input->GetData()->AssignedGamepad<0)
        {
            UE_LOG(LogTemp,Warning,TEXT("?????? %d"),(*ent)->StatefullComponents.size());
            
        }
        if ((*ent)->StatefullComponents.find((*ent)->GetState()) != (*ent)->StatefullComponents.end()) {
            (*ent)->StatefullComponents[(*ent)->GetState()]->Update((*ent));
        }
    }
    TickPhysics();
    TickInputs();
}

void World::Destroy() {
    for (auto ent = entities.begin(); ent != entities.end(); ent++) {
        for(auto comp = (*ent)->Components.cbegin(); comp!=(*ent)->Components.cend(); comp++)
        {
            delete comp->second;
        }
    }
    
    while(entities.size()>0){
        auto entity = entities.front();
        delete entity;
        entities.pop_front();
    }
    VirtualMemory::Clear();
}

void World::TickPhysics()
{
    for(auto ent: World::entities)
    {
        if(!ent->GetData()->active) continue;
        auto velocity= ent->Body->GetData()->Velocity;
        velocity = velocity / Fix(PhysicsPrecision);
        if (velocity.Z != Fix(0.f))
        {
            for (int i = 0; i < PhysicsPrecision; i++)
            {
                auto oldpos = ent->Body->GetData()->Position;
                ent->Body->GetData()->Position.Z+=velocity.Z;
                for(auto ent2: World::entities)
                {
                    if(!ent2->GetData()->active) continue;
                    if(ent==ent2) continue;
                    if(ent->Body->Shape->Collides(ent2->Body->Shape))
                    {
                        ent->Body->GetData()->Position.Z = oldpos.Z;
                        i = PhysicsPrecision+1;
                        break;
                    }
                }
            }
        }
        if (velocity.Y != Fix(0.f))
        {
            for (int i = 0; i < PhysicsPrecision; i++)
            {
                auto oldpos = ent->Body->GetData()->Position;
                ent->Body->GetData()->Position.Y+=velocity.Y;
                for(auto ent2: World::entities)
                {
                    if(!ent2->GetData()->active) continue;
                    if(ent==ent2) continue;
                    if(ent->Body->Shape->Collides(ent2->Body->Shape))
                    {
                        ent->Body->GetData()->Position.Y = oldpos.Y;
                        i = PhysicsPrecision+1;
                        break;
                    }
                }
            }  
        }
        
        if (velocity.X != Fix(0.f))
        {
            for (int i = 0; i < PhysicsPrecision; i++)
            {
                auto oldpos = ent->Body->GetData()->Position;
                ent->Body->GetData()->Position.X+=velocity.X;
                for(auto ent2: World::entities)
                {
                    if(!ent2->GetData()->active) continue;
                    if(ent==ent2) continue;
                    if(ent->Body->Shape->Collides(ent2->Body->Shape))
                    {
                        ent->Body->GetData()->Position.X = oldpos.X;
                        i = PhysicsPrecision+1;
                        break;
                    }
                }
            }
        }


    }
}

void World::TickInputs()
{
    for(auto ent: World::entities)
    {
        if(ent->Input!=nullptr)
        {
            ent->Input->GetData()->PreviousInput =ent->Input->GetData()->Input;  
        }
    }
}

