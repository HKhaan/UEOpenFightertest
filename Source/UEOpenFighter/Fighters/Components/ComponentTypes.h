#pragma once

#include "CoreMinimal.h"
//#include "ComponentTypes.generated.h"

UENUM(BlueprintType)
enum class ComponentTypes : uint8 
{
    InputReceiverComponentType,
    WalkingComponentType,
    KickComponentTypes,
    FighterComponentType,
    BodyComponentType,
    AnimationComponentType,
    HitboxComponentType,
    PunchComponentType,
    IdleComponentType,
};