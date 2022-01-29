#pragma once
#include "Shapes.h"

class Cylinder : public Shapes
{
public:
	Cylinder(int radius, int height)
	{
		Radius= radius;
		Height = height;
		ShapeType = EShapeTypes::CylinderType;
	}
	int Radius;
	int Height;
	virtual bool Collides(Cylinder* cylinder) override;
	virtual bool Collides(Sphere* sphere) override;
	virtual bool Collides(Bound* bound) override;
};
