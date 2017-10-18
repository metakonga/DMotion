#ifndef ALGEBRAMATH_H
#define ALGEBRAMATH_H

#include <cmath>
#include "dmotion_types.h"

static double sin1 = 0;
static double sin2 = 0;
static double cos1 = 0;
static double cos2 = 0;

inline vecd3 operator+(vecd3& a, vecd3& b)
{
	return vecd3(a.X() + b.X(), a.Y() + b.Y(), a.Z() + b.Z());
}

inline vecd3 operator-(vecd3& a, vecd3& b)
{
	return vecd3(a.X() - b.X(), a.Y() - b.Y(), a.Z() - b.Z());
}

inline vecd3 operator*(double a, vecd3& b)
{
	return vecd3(a * b.X(), a * b.Y(), a * b.Z());
}

// inline static void setSinCos(double a1, double a2)
// {
// 	sin1 = sin(a1);
// 	sin2 = sin(a2);
// 	cos1 = cos(a1);
// 	cos2 = cos(a2);
// }

inline transformationMatrix derivateTM(double a)
{
	transformationMatrix TM = { -sin(a), -cos(a), cos(a), -sin(a) };
	return TM;
}

// inline transformationMatrix derivateTM2()
// {
// 	transformationMatrix TM = { -sin2, -cos2, cos2, -sin2 };
// 	return TM;
// }

inline transformationMatrix TM(double a)
{
	transformationMatrix TM = { cos(a), -sin(a), sin(a), cos(a) };
	return TM;
}
// 
// inline transformationMatrix TM2()
// {
// 	transformationMatrix TM = { cos2, -sin2, sin2, cos2 };
// 	return TM;
// }

namespace math
{
	enum tAxis {AX = 0, AY, AZ, AXYZ};

	inline vecd3 local2global(transformationMatrix& A, vecd3& a)
	{
		double x, y;
		x = A.a0 * a.X() + A.a1 * a.Y();
		y = A.a2 * a.X() + A.a3 * a.Y();
		return vecd3(x, y, 0);
	}

	inline vecd3 global2local(transformationMatrix& A, vecd3& a)
	{
		double x, y;
		x = A.a0 * a.X() + A.a2 * a.Y();
		y = A.a1 * a.X() + A.a3 * a.Y();
		return vecd3(x, y, 0);
	}

	inline vecd3 cross(vecd3& a, vecd3& b)
	{
		vecd3 r(-a.Z() * b.Y() + a.Y() * b.Z(),
			a.Z() * b.X() - a.X() * b.Z(),
			-a.Y() * b.X() + a.X() * b.Y());
		return r;
	}

	inline double dot(vecd3& a, vecd3& b)
	{
		double r = a.X() * b.X() + a.Y() * b.Y() + a.Z() * b.Z();
		return r;
	}

	inline double length(vecd3& a, vecd3& b)
	{
		vecd3 d = b - a;
		return sqrt(dot(d, d));
	}
}

#endif