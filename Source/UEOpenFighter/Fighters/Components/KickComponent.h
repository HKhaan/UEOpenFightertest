#pragma once
#include "UEOpenFighter/ECF/Component.h"

struct KickData
{
};

class KickComponent :public RollbackComponent<KickData>
{
public:
	KickComponent();
	static bool CheckShouldTransitionTo(Entity* entity);
	virtual void Update(Entity* entity) override;
};
