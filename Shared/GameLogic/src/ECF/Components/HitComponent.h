#pragma once
#include "ECF/Component.h"

struct KickData
{
};

class HitComponent :public RollbackComponent<KickData>
{
public:
	HitComponent();
	static bool CheckShouldTransitionTo(Entity* entity);
	virtual void Update(Entity* entity) override;
};
