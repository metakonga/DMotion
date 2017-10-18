#include "geometry_wedge.h"
#include <BRepPrimAPI_MakeWedge.hxx>

geometry_wedge::geometry_wedge(QString _name)
	: geometry(_name)
{

}

geometry_wedge::~geometry_wedge()
{

}

void geometry_wedge::Make(double _dx, double _dy, double _dz, double _ltx)
{
	TopoDS_Shape s = BRepPrimAPI_MakeWedge(_dx, _dy, _dz, _ltx);
	geometry::setAIS(s);
}