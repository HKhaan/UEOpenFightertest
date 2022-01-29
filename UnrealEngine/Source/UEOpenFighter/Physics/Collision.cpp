#include "Collision.h"


#include "Shapes/Cylinder.h"
#include "Shapes/Sphere.h"
#include "Shapes/Bound.h"
bool Collision::Collides(Cylinder* cylinder1, Cylinder* cylinder2)
{
	if(cylinder1->Position->Z<cylinder2->Position->Z+cylinder2->Height &&
		cylinder1->Position->Z+cylinder1->Height>cylinder2->Position->Z)
	{
		auto cyl2Lol = *cylinder1->Position;
		cyl2Lol.Z = cylinder1->Position->Z;
		return Vector3::Distance(*cylinder1->Position,cyl2Lol)< Fix(cylinder1->Radius+cylinder2->Radius);
	}
	return false;
}

bool Collision::Collides(Cylinder* cylinder1, Sphere* sphere2)
{
	auto cylPos = *cylinder1->Position;
	if((cylPos.Z> sphere2->Position->Z) &&
		(cylPos.Z + cylinder1->Height < sphere2->Position->Z))
	{
		cylPos.Z = sphere2->Position->Z;
	}
	return Vector3::Distance(cylPos,*sphere2->Position)< Fix(cylinder1->Radius+sphere2->Radius);
} 

bool Collision::Collides(Sphere* sphere1, Sphere* sphere2)
{
	return Vector3::Distance(*sphere1->Position,*sphere2->Position)< Fix(sphere1->Radius+sphere2->Radius);
}

bool Collision::Collides(Bound* bound1, Sphere* sphere2)
{
	auto pos = *sphere2->Position;
	if(bound1->BoundX)
		pos.X= bound1->Position->X;
	else
		pos.Y= bound1->Position->Y;
	return Vector3::Distance(pos,*sphere2->Position)< Fix(sphere2->Radius);
	
}

bool Collision::Collides(Bound* bound1, Bound* bound2)
{
	return false;
}

bool Collision::Collides(Cylinder* Cylinde1, Bound* bound1)
{
	auto pos = *Cylinde1->Position;
	if(bound1->BoundX)
		pos.X= bound1->Position->X;
	else
		pos.Y= bound1->Position->Y;
	return Vector3::Distance(pos,*Cylinde1->Position)< Fix(Cylinde1->Radius);
}
