#pragma once


#include "UEOpenFighter/ECF/Component.h"

struct WalkingData{
public:
    WalkingData(){
        
    }
    
};

class WalkingComponent: public RollbackComponent<WalkingData> {
public:
    virtual void Update(Entity* entity) override;
    static bool CheckShouldTransitionTo(Entity* entity);

};