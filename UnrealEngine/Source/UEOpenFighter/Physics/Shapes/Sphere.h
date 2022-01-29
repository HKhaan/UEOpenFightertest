#pragma once
#include "Shapes.h"

class Sphere : public Shapes
{
public:
	Sphere(int radius)
	{
		ShapeType = EShapeTypes::SphereType;
		Radius = radius;
	}
	int Radius;
	virtual bool Collides(Cylinder* cylinder) override;
	virtual bool Collides(Sphere* sphere) override;
	virtual bool Collides(Bound* bound) override;
};
