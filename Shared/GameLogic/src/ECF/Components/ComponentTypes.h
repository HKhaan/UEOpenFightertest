#pragma once

#include "CoreMinimal.h"
//#include "ComponentTypes.generated.h"

UENUM(BlueprintType)
enum class ComponentTypes : uint8 
{
    InputReceiverComponentType,
    WalkingComponentType,
    HitComponentType,
    FighterComponentType,
    BodyComponentType,
    AnimationComponentType,
    HitboxComponentType,
    IdleComponentType,
};