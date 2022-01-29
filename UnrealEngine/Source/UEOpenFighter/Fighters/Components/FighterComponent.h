#pragma once
#include "UEOpenFighter/Data/Fighter.h"
#include "UEOpenFighter/ECF/Component.h"
#include "UEOpenFighter/ECF/Entity.h"

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
