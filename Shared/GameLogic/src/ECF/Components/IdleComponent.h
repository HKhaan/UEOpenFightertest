#pragma once
#include "Data/Fighter.h"
#include "ECF/Component.h"
#include "ECF/Entity.h"

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
