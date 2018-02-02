#ifndef DRIVING_CONSTRAINT_H
#define DRIVING_CONSTRAINT_H

#include "constraint.h"

class drivingConstraint : public constraint
{
public:
	drivingConstraint(QString _name);
	virtual ~drivingConstraint();

	void runFunction(double ct);
	double MaxVelocityTime();
	double MaxVelocity();
	QString FilePath();

	//void setFunction(double(*_func)(double));
	void setConstantVelocity(double _c_vel);
	void setTargetBody(rigidBody* _rb, coordinateType _ct);
	bool setVelocityProfile(QString _path);
	void setPreviousPosition();
	void bindGeneralizedCoordinate(VECD& q);
	void bindTime(double _dt, double* _ct, unsigned int* _cs);
	double ConstantVelocity();
	void initializeDrivingPosition();
	QVector<double>& VelocityProfile();
	QPointF TimeVelocity(int idx);
	void derivativeInterp(VECD &rhs, unsigned int i, unsigned int rstep);
	void testConstraintJacobian(VECD &q, VECD& qd, unsigned int i, double mul = 0);

	virtual int constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul = 0);
	virtual void constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int i, bool isjp = false);
	virtual void derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i);
	virtual void lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1 = 0, double mul = 1);

private:
	QString name;
	QString file;
	//double funcValue;
	unsigned int *cs;
	double dt;
	double *gp;
	double *ct;
	double p_pos;
	double pos_0;
	double c_vel;
	double maxAbsVel;
	double maxTime;
	coordinateType ctype;
	rigidBody *targetBody;
	QVector<double> time;
	QVector<double> velProfile;
	QVector<double> dvelProfile;
	QVector<double> ddvelProfile;
};

#endif