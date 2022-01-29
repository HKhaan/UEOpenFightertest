#include "Shapes.h"

bool Shapes::Collides(Shapes* shape)
{
	switch (shape->ShapeType)
	{
	case SphereType: 
		return Collides((Sphere*)shape);
	case CylinderType:
		return Collides((Sphere*)shape);
	case BoundType:
		return Collides((Bound*)shape);
	default: break;
	}
	return false;
}
