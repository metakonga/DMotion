#ifndef GEOMETRY_WEDGE_H
#define GEOMETRY_WEDGE_H

#include "geometry.h"


class geometry_wedge : public geometry
{
public:
	geometry_wedge(QString _name);
	~geometry_wedge();

	void Make(double _dx, double _dy, double _dz, double _ltx);

private:

	double dx;
	double dy;
	double dz;
	double ltx;
};

#endif