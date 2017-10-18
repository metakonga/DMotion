#include "geometry.h"


geometry::geometry(QString _name)
	: name(_name)
{

}

geometry::~geometry()
{

}

void geometry::setAIS(const TopoDS_Shape& ts)
{
	ais = new AIS_Shape(ts);
}

Handle(AIS_Shape) geometry::AIS()
{
	return ais;
}