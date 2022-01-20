#pragma once
#include "UEOpenFighter/Data/Fighters.h"
#include "UEOpenFighter/ECF/Component.h"
#include "UEOpenFighter/ECF/Entity.h"

struct HitboxData
{
public:
	HitboxData()
	{
	}

};
class HitboxComponent: public  RollbackComponent<HitboxData>
{
public:
	void Update(Entity* entity) override;
};
