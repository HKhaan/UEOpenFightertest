#pragma once
#include "UEOpenFighter/Data/Fighters.h"
#include "UEOpenFighter/ECF/Component.h"
#include "UEOpenFighter/ECF/Entity.h"

struct IdleData
{
public:
	IdleData()
	{
	}
};
class IdleComponent: public  RollbackComponent<IdleData>
{
public:
	void Update(Entity* entity) override;
	static bool CheckShouldTransitionTo(Entity* entity);

};
