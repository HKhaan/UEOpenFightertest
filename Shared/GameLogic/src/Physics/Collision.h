#pragma once

class Sphere;
class Bound;
class Cylinder;

class Collision
{
public:
	static bool Collides(Cylinder* cylinder1, Cylinder* cylinder2);
	static bool Collides(Cylinder* cylinder1, Sphere* sphere2);
	static bool Collides(Sphere* sphere1, Sphere* sphere2);

	static bool Collides(Bound* bound1, Sphere* sphere2);
	static bool Collides(Bound* bound1, Bound* bound2);
	static bool Collides(Cylinder* Cylinde1, Bound* bound1);
};
