#pragma once

#include "UEOpenFighter/ECF/Component.h"
#include "UEOpenFighter/Physics/Vector3.h"
#include "UEOpenFighter/Physics/Shapes/Shapes.h"
struct BodyData{
    BodyData()
    {
        Radius=100;
        Position = Vector3();
        Velocity = Vector3();
        Rotation = Vector3();
    }
    Vector3 Position;
    Vector3 Velocity;
    Vector3 Rotation;
    int      Radius;
    
};

class BodyComponent: public RollbackComponent<BodyData> {
public:
    //TODO: Make shape changeable and delete in destructor (add destructor system to components)
    Shapes* Shape=nullptr;
    virtual void BeginPlay(Entity* entity) override;
    virtual void Update(Entity* entity) override;
    void FixStageCollisions();
    bool CheckPositionCollides(Entity* entity);
    Vector3 PredictPosition(Entity* ent, int frames);
    ~BodyComponent();
};