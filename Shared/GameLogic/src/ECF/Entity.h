#pragma once
#include "ECF/Component.h"
#include "Data/Fighter.h"
#include "ECF/Components/ComponentTypes.h"
#include <map>
class UFMODEvent;
class AUEOpenFighterCharacter;
class Component;
struct FFighter;
class BodyComponent;
class AnimationComponent;
class InputReceiverComponent;
struct AudioRollbackComponent
{
    UFMODEvent* Sound;
    int CurrentFrame;
    AudioRollbackComponent()
    {
        Sound=nullptr;
        CurrentFrame=0;
    }
};

struct EntityData {
    EFightState currentState;
    bool active;
    AudioRollbackComponent Channel1;
    EntityData()
    {
        currentState=EFightState::Idle;
        active=false;
        Channel1 = AudioRollbackComponent();
    }
    
};

class Entity {
    friend class ComponentFactory;
    friend class World;
private:
    Entity(){};
    
private:
    ComponentDataCreator<EntityData>* data = ComponentDataCreator<EntityData>::CreateDataForComponent();
public:
    std::map<ComponentTypes, Component*> Components;
    std::map<ComponentTypes, Component*> StatelessComponents;
    std::map<EFightState, Component*> StatefullComponents;
    Component* GetComponent(ComponentTypes componentType);
    AUEOpenFighterCharacter* Actor=nullptr;
    UFighter* FighterData=nullptr;
    BodyComponent* Body=nullptr;
    AnimationComponent* Animator=nullptr;
    InputReceiverComponent* Input=nullptr;
    EntityData* GetData() { return data->data; }
    void SetState(EFightState state);
    EFightState GetState();
};