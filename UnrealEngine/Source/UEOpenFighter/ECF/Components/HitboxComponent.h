#pragma once
#include "UEOpenFighter/Data/Fighter.h"
#include "UEOpenFighter/ECF/Component.h"
#include "UEOpenFighter/ECF/Entity.h"
#include "UEOpenFighter/Physics/Vector3.h"

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

	static int HurtboxCount(Entity* entity);
	static Vector3 GetHurtboxPosition(Entity* entity, int index);
	static int HitboxCount(Entity* entity);
	static Vector3 GetHitboxPosition(Entity* entity, int index);
};
