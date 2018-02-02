#ifndef DMOTION_TYPES_H
#define DMOTION_TYPES_H

#include <gp_Pnt.hxx>
#include <QString>
#include <QList>
#include <QPointF>
#include "matrix.hpp"
#include "vector.hpp"
#include "sparse_matrix.hpp"

#define kor(str) QString::fromLocal8Bit(str)

typedef gp_Pnt vecd3;
typedef algebra::matrix<double> MATD;
typedef algebra::vector<double> VECD;
typedef xdyn::sparse_matrix<double> SMATD;

struct hardPoint{ QString name; vecd3 loc0; vecd3 loc; };
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
	double time, fx, fy, tr;// , fz, rm, rx, ry, rz;
	vecd3 loc;
};

struct stResultSet
{
	QString caseName;
	QString dir;
	double AT_FY;
	double AT_TR;
	double ALR_FX;
	double ALR_FY;
	double LCR_FX;
	double LCR_FY;
	double CGR_FX;
	double CGR_FY;
	double PT_FY;
	double PT_TR;
	double PF_FX;
	double PF_FY;
};

struct stMaxReaction
{
	QString dir;
	double time;
	double maximum;
};

struct plotInfo
{
	QPointF x_range;
	QPointF y_range;
	QString x_title;
	QString y_title;
};

inline QString ReactionForceTypeStringByIndex(int i)
{
	QString str;
	switch (i)
	{
	case 0: str = "Nozzle Trans.(FY)"; break;
	case 1: str = "Nozzle Trans.(TR)"; break;
	case 2: str = "Nozzle-Link Rev.(FX)"; break;
	case 3: str = "Nozzle-Link Rev.(FY)"; break;
	case 4: str = "Link Vertical (FY)"; break;
	case 5: str = "Link-Hinge Rev.(FX)"; break;
	case 6: str = "Link-Hinge Rev.(FY)"; break;
	case 7: str = "Hinge-Cam Rev.(FX)"; break;
	case 8: str = "Hinge-Cam Rev.(FY)"; break;
	case 9: str = "Link-Cam Rev.(FX)"; break;
	case 10: str = "Link-Cam Rev.(FY)"; break;
	case 11: str = "Cam-Ground Rev.(FX)"; break;
	case 12: str = "Cam-Ground Rev.(FY)"; break;
	case 13: str = "Arc Vertical (FY)"; break;
	case 14: str = "Arc Rotation (TR)"; break;
	case 15: str = "Arc Trans.(FY)"; break;
	case 16: str = "Arc Trans.(TR)"; break;
	case 17: str = "Profile (FX)"; break;
	case 18: str = "Profile (FY)"; break;
	}
	return str;
}

enum jointType{ NO_TYPE = 0, REVOLUTE, TRANSLATION, DRIVING, POINTFOLLOWER, SIMPLIFIED, CONSTANT };
enum coordinateType{ AXIS_X = 0, AXIS_Y, AXIS_Z, AXIS_R };
enum comparisonReactionType{ ONLY_ONE = 0, SMALLER_FIRST, USER_SELECTED };
enum coordinates{ POSITION_X = 0, POSITION_Y, ANGLE, VELOCITY_X, VELOCITY_Y, ANGULAR_VELOCITY, ACCELERATION_X, ACCELERATION_Y, ANGULAR_ACCELERATION };
enum modelType{ ORIGINAL_CAM_TYPE = 0, HOLE_CAM_TYPE };
enum reactionForceType{ NOZZLE_TRANS_FY = 0, NOZZLE_TRANS_TR, NOZZLE_LINK_REV_FX, NOZZLE_LINK_REV_FY, 
	LINK_SIMPLE_FY,
	LINK_HINGE_REV_FX, LINK_HINGE_REV_FY, HINGE_CAM_REV_FX, HINGE_CAM_REV_FY, 
	LINK_CAM_REV_FX, LINK_CAM_REV_FY, CAM_GROUND_REV_FX, CAM_GROUND_REV_FY,
	ARC_SIMPLE_FY, ARC_SIMPLE_TR,
//	ARC_ROLLER_REV_FX, ARC_ROLLER_REV_FY,
	ARC_TRANS_FY, ARC_TRANS_TR, PROFILE_FX, PROFILE_FY, NO_REACTION_TYPE };

#endif