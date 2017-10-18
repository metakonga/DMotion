#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <QString>
#include <QVector>
#include "algebraMath.h"

class rigidBody
{
public:
	rigidBody(QString _name);
	~rigidBody();

	//void define(double mass, vecd3 inertia, vecd3 _pos, vecd3 _ang);
	void appendResultData(resultDataType rdt);
	void clearResultData();

	void setID(unsigned int _id);
	void setName(QString _name);
	void setMass(double _mass);
	void setInertia(double izz);
	void setPosition(double x, double y, double z);
	void setPosition2GP(double x, double y, double z);
	void setVelocity(double x, double y, double z);
	void setVelocity2GV(double x, double y, double z);
	void setAngle(double v);
	void setAngularVelocity(double v);
	void setGround(bool b);
	void setShapePath(QString _path);
	void setGeneralCoordinatePointer(double* _gp, double* _gv);
	
	QString Name();
	double Mass();
	double Inertia();
	vecd3 Position();
	vecd3 PositionFromGP();
	vecd3 Velocity();
	double Angle();
	double AngularVelocity();
	transformationMatrix& DerivateTM();
	transformationMatrix& TM();
	unsigned int ID();
	bool IsGround();
	QVector<resultDataType>* ResultData();
	QString ShapePath();

private:
	void setDerivateTM();
	void setTM();
	bool _isGround;
	unsigned int id;
	QString name;
	QString shapePath;
	double mass;
	double inertia;
	double* gp_ptr;
	double* gv_ptr;
	vecd3 pos;
	vecd3 vel;
	double ang;
	double angv;
	transformationMatrix A;
	transformationMatrix dA;

	QVector<resultDataType> results;

	static unsigned int count; 
};

#endif