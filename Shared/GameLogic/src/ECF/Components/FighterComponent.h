#pragma once
#include "Data/Fighter.h"
#include "ECF/Component.h"
#include "ECF/Entity.h"

struct FighterData
{
public:
	FighterData()
	{
		Health=100;
	}
	int Health;
	

};
class FighterComponent: public  RollbackComponent<FighterData>
{
public:
	void Update(Entity* entity) override;
	
};
