#pragma once


#include "UEOpenFighter/ECF/Component.h"

struct WalkingData{
public:
    WalkingData(){
        Jumping = false;
        JumpVal = 0;
    }
    bool Jumping;
    int JumpVal;
};

class WalkingComponent: public RollbackComponent<WalkingData> {
public:
    virtual void Update(Entity* entity) override;
    static bool CheckShouldTransitionTo(Entity* entity);

};