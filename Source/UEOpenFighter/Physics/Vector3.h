// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UEOpenFighter/Misc/fpm/fixed.hpp"
#include "UEOpenFighter/Misc/fpm/math.hpp"
#include "Kismet/KismetMathLibrary.h"

/**
 * 
 */

struct Vector3
{
public:
	Fix X;
	Fix Y;
	Fix Z;

	Vector3()
	{
		X = Fix(0);
		Y = Fix(0);
		Z = Fix(0);
	}

	Vector3(Fix x, Fix y, Fix z)
	{
		X = Fix(x);
		Y = Fix(y);
		Z = Fix(z);
	}

	
	/* Scale vector so it's length is 1 */
	void normalize();

	/* Vector length */
	Fix magnitude() const;

	/* Same as magnitude, but w/o sqrt: faster, but is not real length */
	Fix amplitude() const;

	/* Arithmetic operators with other vectors and scalars */
	Vector3 operator+(const Vector3& v2) const;
	Vector3 operator-(const Vector3& v2) const;
	Vector3 operator*(const Fix value) const;
	Vector3 operator/(const Fix value) const;

	/* Value changing operators */
	Vector3& operator*=(const Fix value);
	Vector3& operator+=(const Vector3& v2);

	/* Comparison operators */
	int operator==(const Vector3& v2) const;
	int operator!=(const Vector3& v2) const;

	// int Size()
	// {
	// 	return (X * X + Y * Y + Z * Z);
	// }
	static Fix Dot(Vector3 vector1, Vector3 vector2);

	void setZero()
	{
		X = Fix(0);
		Y = Fix(0);
		Z = Fix(0);
	}


	Vector3 LookAt(Vector3 a);

	Fix sin(Fix val)
	{
		
		return Fix(-1) * fpm::sin(val * Fix(0.01745329251));
	}

	Fix cos(Fix val)
	{
		return Fix(-1) * fpm::cos(val * Fix(0.01745329251));
	}

	Vector3 Right()
	{
		return Vector3(-1 * sin(Z + Fix(90)), cos(Z + Fix(90)), Fix(0)) * Fix(-1);
		//auto res = Vector3(FMath::DegreesToRadians(FMath::Sin(Y)), 0, FMath::DegreesToRadians(FMath::Cos(Y)));
		//return Vector3(0, 0, 1);
	}


	static Vector3 Up()
	{
		return Vector3(Fix(0), Fix(1), Fix(0));
	}

	Vector3 Forward()
	{
		return Vector3(Fix(-1) * sin(Z), Fix(0), cos(Z)) * Fix(-1);
		//return Vector3(1, 0, 0);
		//return Vector3(FMath::DegreesToRadians(FMath::Sin(Y+90.0f)), 0, FMath::DegreesToRadians(FMath::Cos(Y+90.0f)));
	}



	Vector3 Forward2()
	{
		return Vector3(sin(Y + Fix(90)), Fix(0), fpm::sin(Y + Fix(90)));
	}


	FVector ToFVector() // by-value param invokes class copy-ctor
	{
		FVector b;
		b.X = ((float)this->X) ;
		b.Y = ((float)this->Y) ;
		b.Z = ((float)this->Z) ;
		return b;
	}

	static Vector3 FromFVector(FVector val) // by-value param invokes class copy-ctor
	{
		Vector3 b;
		b.X = Fix((val.X));
		b.Y = Fix((val.Y));
		b.Z = Fix((val.Z));
		return b;
	}
	static Vector3 FromIntFVector(FIntVector val) // by-value param invokes class copy-ctor
        {
		Vector3 b;
		b.X = Fix((val.X));
		b.Y = Fix((val.Y));
		b.Z = Fix((val.Z));
		return b;
        }

	static Fix Distance(const Vector3& Pos1, const Vector3& Pos2)
	{
		return fpm::sqrt(fpm::pow(Pos2.X - Pos1.X, 2) + fpm::pow(Pos2.Z - Pos1.Z, 2) + fpm::pow(Pos2.Y - Pos1.Y, 2));
	}


};
