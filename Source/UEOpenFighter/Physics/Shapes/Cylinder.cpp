#include "Cylinder.h"
#include "../Collision.h"
bool Cylinder::Collides(Cylinder* cylinder)
{
	return Collision::Collides(this,cylinder);
}

bool Cylinder::Collides(Sphere* sphere)
{
	return Collision::Collides(this,sphere);
}

bool Cylinder::Collides(Bound* bound)
{
	return Collision::Collides(this,bound);
}
