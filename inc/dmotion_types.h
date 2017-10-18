#ifndef DMOTION_TYPES_H
#define DMOTION_TYPES_H

#include <gp_Pnt.hxx>
#include <QString>
#include <QList>
#include "matrix.hpp"
#include "vector.hpp"
#include "sparse_matrix.hpp"

typedef gp_Pnt vecd3;
typedef algebra::matrix<double> MATD;
typedef algebra::vector<double> VECD;
typedef xdyn::sparse_matrix<double> SMATD;

struct hardPoint{ QString name; vecd3 loc; };
struct gravity{ double x, y, z; };
struct transformationMatrix{ double a0, a1, a2, a3; };
struct resultDataType
{ 
	double time;
	vecd3 pos, vel, acc;
	double ang, angv, anga;
};

struct jointResultDataType
{
	double time, fm, fx, fy, fz, rm, rx, ry, rz;
	vecd3 loc;
};

enum jointType{ NO_TYPE = 0, REVOLUTE, TRANSLATION, DRIVING };
enum coordinateType{ AXIS_X = 0, AXIS_Y, AXIS_Z };

#endif