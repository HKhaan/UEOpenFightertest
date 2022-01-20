// Fill out Your copYright notice in the Description page of Project Settings.


#include "Vector3.h"
//
// Vector3::Vector3()
// {
// }
//
// Vector3::~Vector3()
// {
// }

void Vector3::normalize() {
	Fix mag = this->magnitude();
	X /= mag;
	Y /= mag;
	Z /= mag;
}

Fix Vector3::magnitude() const {
	return (Fix) sqrt( this->X * this->X + this->Y * this->Y + this->Z * this->Z );
}

Fix Vector3::amplitude() const {
	return this->X * this->X + this->Y * this->Y + this->Z * this->Z;
}

Vector3 Vector3::operator+(const Vector3 &v2) const {
	return Vector3(this->X + v2.X, this->Y + v2.Y, this->Z + v2.Z);
}

Vector3 Vector3::operator-(const Vector3 & v2) const {
	return Vector3(this->X - v2.X, this->Y - v2.Y, this->Z - v2.Z);
}

Vector3 Vector3::operator*(const Fix value) const {
	return Vector3(this->X * value, this->Y * value, this->Z * value);
}

Vector3 Vector3::operator/(const Fix value) const {
	return Vector3(this->X / value, this->Y / value, this->Z / value);
}

Vector3& Vector3::operator*=(const Fix value) {
	this->X *= value;
	this->Y *= value;
	this->Z *= value;
	return *this;
}

Vector3 & Vector3::operator+=(const Vector3 & v2) {
	this->X += v2.X;
	this->Y += v2.Y;
	this->Z += v2.Z;
	return *this;
}

int Vector3::operator==(const Vector3 & v2) const {
	return this->X == v2.X && this->Y == v2.Y && this->Z == v2.Z;
}

int Vector3::operator!=(const Vector3 & v2) const {
	return !(this->X == v2.X && this->Y == v2.Y && this->Z == v2.Z);
}

