#ifndef SIMPLIFIEDCONSTRAINT_H
#define SIMPLIFIEDCONSTRAINT_H

#include "constraint.h"

class simplifiedConstraint : public constraint
{
public:
	enum DRIECTION{HORIZONTAL = 0, VERTICAL, ROTATION};
	simplifiedConstraint(QString _name);
	~simplifiedConstraint();

	void setConstantValue(double _y = 0);
	void setConstantValueFromBaseBody();
	void setPositionFromHardPoint();
	void setDirection(DRIECTION _direction);

	DRIECTION Direction();

	virtual int constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul = 0);
	virtual void constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int i, bool isjp = false);
	virtual void derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i);
	virtual void lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1 = 0, double mul = 1);

private:
	DRIECTION direction;
	double ivalue;
};

#endif