#pragma once
#include "Shapes.h"

class Bound : public Shapes
{
public:
	Bound(bool bound)
	{
		ShapeType = EShapeTypes::BoundType;
		BoundX=bound;
	}
	bool BoundX;
};
