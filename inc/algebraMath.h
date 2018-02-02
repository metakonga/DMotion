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

#define checkMinus(v) v < 0 ? -1 : 1

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

	inline double length(vecd3& a)
	{
		return sqrt(dot(a, a));
	}

	inline int roundv(double d, bool isUp)
	{
		if (d > -1e-9 && d < 1e-9)
		{
			return 0;
		}
		int sg = checkMinus(d);
		double ad = abs(d);
		if (ad < 0)
		{
			double ad = abs(d);
			if (ad > 0 && ad < 0.2) return 0.2 * sg;
			else if (ad >= 0.2 && ad < 0.4) return 0.4 * sg;
			else if (ad >= 0.4 && ad < 0.6) return 0.6 * sg;
			else if (ad >= 0.6 && ad < 0.8) return 0.8 * sg;
			else if (ad >= 0.8 && ad < 1.0) return 1.0 * sg;
			else if (ad >= 0.01 && ad < 0.02) return 0.02 * sg;
			else if (ad >= 0.02 && ad < 0.04) return 0.04 * sg;
			else if (ad >= 0.04 && ad < 0.06) return 0.06 * sg;
			else if (ad >= 0.06 && ad < 0.08) return 0.08 * sg;
			else if (ad >= 0.08 && ad < 0.1) return 0.1 * sg;
			else if (ad >= 0.001 && ad < 0.002) return 0.002 * sg;
			else if (ad >= 0.002 && ad < 0.004) return 0.004 * sg;
			else if (ad >= 0.004 && ad < 0.006) return 0.006 * sg;
			else if (ad >= 0.006 && ad < 0.008) return 0.08 * sg;
			else if (ad >= 0.008 && ad < 0.01) return 0.01 * sg;
			else if (ad >= 0.0001 && ad < 0.0002) return 0.0002 * sg; 
		}
		QString c_v = QString("%1").arg(round(d));
		
		int sz = c_v.size() + (sg < 0 ? -1 : 0);
		int add = 0;
		double up = 0;
		if (sg == 1) sg = 1;
		switch (sz)
		{
		case 1: up = 1.1; add = 1; break;
		case 2: up = 9; add = 10; break;
		case 3: up = 9; add = 10; break;
		case 4: up = 99; add = 100; break;
		case 5: up = 999; add = 1000; break;
		case 6: up = 9999; add = 10000; break;
		case 7: up = 99999; add = 100000; break;
		case 8: up = 999999; add = 1000000; break;
		case 9: up = 9999999; add = 10000000; break;
		case 10: up = 99999999; add = 100000000; break;
		case 11: up = 999999999; add = 1000000000; break;
		}
		double v = 0;
		if (isUp)
		{
			int dv = (c_v.toDouble() + up) / (double)(add);
			v = dv * add;// / (double)(add + 1);
		}
		else
		{
			int dv = (c_v.toDouble() - up) / (double)(add);
			v = dv * add;
		}
		
		//double rv = sg == 1 ? floor(v) : ceil(v);
		return v;// rv * (add + 1);
	}
}

#endif