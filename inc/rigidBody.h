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
	void setMass(double _mass, bool with0 = false);
	void setInertia(double izz, bool with0 = false);
	void setPosition(double x, double y, double z, bool with0 = false);
	void setPosition2GP(double x, double y, double z);
	void setVelocity(double x, double y, double z, bool with0 = false);
	void setAcceleration(double x, double y, double z, bool with0 = false);
	void setVelocity2GV(double x, double y, double z);
	void setAngle(double v, bool with0 = false);
	void setAngularVelocity(double v, bool with0 = false);
	void setAngularAcceleration(double v, bool with0 = false);
	void setGround(bool b);
	void setShapePath(QString _path);
	void setGeneralCoordinatePointer(double* _gp, double* _gv);
	void setAnalysis(bool _b);
	void setCoordinateNumber(unsigned int nc);
	void setPosition0();
	void setBody0();
	void setBodyFromBody0();
	
	void initializeBody();
	//double getVariableFromResult(unsigned int step, coordinates coo);
	resultDataType getResult(unsigned int s);

	QString Name();
	double Mass();
	double Mass0();
	double Inertia();
	double Inertia0();
	vecd3 Position();
	vecd3 Position0();
	vecd3 PositionFromGP();
	vecd3 Velocity();
	vecd3 Velocity0();
	vecd3 Acceleration();
	vecd3 Acceleration0();
	double Angle();
	double Angle0();
	double AngularVelocity();
	double AngularVelocity0();
	double AngularAcceleration();
	double AngularAcceleration0();
	transformationMatrix& DerivateTM();
	transformationMatrix& TM();
	unsigned int ID();
	bool IsGround();
	bool IsAnalysis();
	QVector<resultDataType>* ResultData();
	QString ShapePath();
	unsigned int NCoordinates();
	static void initStaticVariable();

protected:
	void setDerivateTM();
	void setTM();
	bool _isAnalysis;
	bool _isGround;
	unsigned int nCoordinates;
	unsigned int id;
	QString name;
	QString shapePath;
	double mass;
	double mass0;
	double inertia;
	double inertia0;
	double* gp_ptr;
	double* gv_ptr;
	vecd3 pos0;
	vecd3 pos;
	vecd3 vel0;
	vecd3 vel;
	vecd3 acc;
	vecd3 acc0;
	double ang;
	double ang0;
	double angv;
	double angv0;
	double anga;
	double anga0;
	transformationMatrix A;
	transformationMatrix dA;

	QVector<resultDataType> results;

	static unsigned int count; 
};

#endif