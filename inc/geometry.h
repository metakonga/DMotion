#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <AIS_Shape.hxx>
#include <TopoDS_Shape.hxx>
#include <QString>

class geometry
{
public:
	geometry(QString _name);
	~geometry();

	void setAIS(const TopoDS_Shape& ts);
	Handle(AIS_Shape) AIS();

protected:
	QString name;

	Handle(AIS_Shape) ais;
};

#endif