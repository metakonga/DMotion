#include "rigidBody.h"

unsigned int rigidBody::count = 0;

rigidBody::rigidBody(QString _name)
	: name(_name)
	, mass(0)
	, inertia(0)
	, ang(0)
	, angv(0)
	, anga(0)
	, _isGround(false)
{
	setTM();
	setDerivateTM();
	id = count++;
	shapePath = "None";
}

rigidBody::~rigidBody()
{

}

void rigidBody::setCoordinateNumber(unsigned int nc)
{
	nCoordinates = nc;
}

void rigidBody::setPosition0()
{
	pos0 = pos;
}

void rigidBody::initializeBody()
{
	pos = pos0;
	vel = vecd3(0.0, 0.0, 0.0);
	acc = vecd3(0.0, 0.0, 0.0);
	ang = 0.0;
	angv = 0.0;
	anga = 0.0;
	setTM();
	setDerivateTM();
	clearResultData();
}

void rigidBody::setName(QString _name)
{
	name = _name;
}

void rigidBody::setMass(double _mass)
{
	mass = _mass;
}

void rigidBody::setInertia(double izz)
{
	inertia = izz;
}

void rigidBody::setPosition(double x, double y, double z)
{
	pos = vecd3(x, y, z);
}

void rigidBody::setVelocity(double x, double y, double z)
{
	vel = vecd3(x, y, z);
}

void rigidBody::setAcceleration(double x, double y, double z)
{
	acc = vecd3(x, y, z);
}

void rigidBody::setAngle(double v)
{
	ang = v;
	setTM();
	setDerivateTM();
}

void rigidBody::setAngularVelocity(double v)
{
	angv = v;
}

void rigidBody::setAngularAcceleration(double v)
{
	anga = v;
}

unsigned int rigidBody::NCoordinates()
{
	return nCoordinates;
}

resultDataType rigidBody::getResult(unsigned int s)
{
	return results.at(s);
}
// double rigidBody::getVariableFromResult(unsigned int step, coordinates coo)
// {
// 	
// }

QString rigidBody::Name()
{
	return name;
}

double rigidBody::Mass()
{
	return mass;
}

double rigidBody::Inertia()
{
	return inertia;
}

vecd3 rigidBody::Position()
{
	return pos;
}

vecd3 rigidBody::Position0()
{
	return pos0;
}

vecd3 rigidBody::Velocity()
{
	return vel;
}

vecd3 rigidBody::Acceleration()
{
	return acc;
}

double rigidBody::Angle()
{
	return ang;
}

double rigidBody::AngularVelocity()
{
	return angv;
}

double rigidBody::AngularAcceleration()
{
	return anga;
}

void rigidBody::setTM()
{
	A.a0 = cos(ang); A.a1 = -sin(ang);
	A.a2 = sin(ang); A.a3 = cos(ang);
}

void rigidBody::setDerivateTM()
{
	dA.a0 = -sin(ang); dA.a1 = -cos(ang);
	dA.a2 = cos(ang); dA.a3 = -sin(ang);
}

transformationMatrix& rigidBody::TM()
{
	return A;
}

transformationMatrix& rigidBody::DerivateTM()
{
	return dA;
}

unsigned int rigidBody::ID()
{
	return id;
}

void rigidBody::setGround(bool b)
{
	_isGround = b;
}

bool rigidBody::IsGround()
{
	return _isGround;
}

void rigidBody::setID(unsigned int _id)
{
	id = _id;
}

void rigidBody::appendResultData(resultDataType rdt)
{
	results.push_back(rdt);
}

void rigidBody::clearResultData()
{
	if (results.size())
		results.clear();
}

QVector<resultDataType>* rigidBody::ResultData()
{
	return &results;
}

void rigidBody::setShapePath(QString _path)
{
	shapePath = _path;
}

void rigidBody::setAnalysis(bool _b)
{
	_isAnalysis = _b;
}

bool rigidBody::IsAnalysis()
{
	return _isAnalysis;
}

QString rigidBody::ShapePath()
{
	return shapePath;
}

void rigidBody::setGeneralCoordinatePointer(double* _gp, double* _gv)
{
	gp_ptr = _gp;
	gv_ptr = _gv;
}

void rigidBody::setPosition2GP(double x, double y, double z)
{
	gp_ptr[0] = x;
	gp_ptr[1] = y;
	gp_ptr[2] = z;
}

void rigidBody::setVelocity2GV(double x, double y, double z)
{
	gv_ptr[0] = x;
	gv_ptr[1] = y;
	gv_ptr[2] = z;
}

vecd3 rigidBody::PositionFromGP()
{
	vecd3 v3(gp_ptr[0], gp_ptr[1], gp_ptr[2]);
	return v3;
}


