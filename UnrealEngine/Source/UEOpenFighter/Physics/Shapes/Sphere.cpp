#include "Sphere.h"

#include "../Collision.h"

bool Sphere::Collides(Cylinder* cylinder)
{
	return Collision::Collides(cylinder,this);
}

bool Sphere::Collides(Sphere* sphere)
{
	return Collision::Collides(this,sphere);
}

bool Sphere::Collides(Bound* bound)
{
	return Collision::Collides(bound,this);
}
