#ifndef VERTICALCONSTRAINT_H
#define VERTICALCONSTRAINT_H

#include "constraint.h"

class verticalConstraint : public constraint
{
public:
	verticalConstraint(QString _name);
	~verticalConstraint();

	void defineInitialVerticalValue(double _y);

	virtual int constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul = 0);
	virtual void constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int i, bool isjp = false);
	virtual void derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i);
	virtual void lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1 = 0, double mul = 1);

private:
	double ivalue;
};

#endif