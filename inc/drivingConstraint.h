#ifndef DRIVING_CONSTRAINT_H
#define DRIVING_CONSTRAINT_H

#include "constraint.h"

class drivingConstraint : public constraint
{
public:
	drivingConstraint(QString _name);
	~drivingConstraint();

	void runFunction(double ct);

	//void setFunction(double(*_func)(double));
	void setConstantVelocity(double _c_vel);
	void setTargetBody(rigidBody* _rb, coordinateType _ct);
	void setVelocityProfile(QString _path);
	void setPreviousPosition();
	void bindGeneralizedCoordinate(VECD& q);
	void bindTime(double _dt, double* _ct, unsigned int* _cs);
	double ConstantVelocity();

	virtual void constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul = 0);
	virtual void constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int i);
	virtual void derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i);
	virtual void lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1 = 0, double mul = 1);

private:
	QString name;
	//double funcValue;
	unsigned int *cs;
	double dt;
	double *gp;
	double *ct;
	double p_pos;
	double pos_0;
	double c_vel;
	coordinateType ctype;
	rigidBody *targetBody;
	QVector<double> velProfile;
};

#endif