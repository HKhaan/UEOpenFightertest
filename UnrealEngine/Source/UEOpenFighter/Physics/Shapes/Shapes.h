#pragma once
#include "../Vector3.h"

class Sphere;
class Cylinder;
class Bound;
class Body;
enum EShapeTypes
{
	SphereType,
	CylinderType,
	BoundType
};
class Shapes
{
public:
	virtual ~Shapes() = default;
	Vector3* Position;
	EShapeTypes ShapeType;
	virtual bool Collides(Shapes* sphere);
	virtual bool Collides(Sphere* sphere){return false;};
	virtual bool Collides(Cylinder* cylinder){return false;};
	virtual bool Collides(Bound* cylinder){return false;};
};
