#ifndef CONSTANTCONSTRAINT_H
#define CONSTANTCONSTRAINT_H

#include "constraint.h"

class constantConstraint : public constraint
{
public:
	enum targetAXIS{TARGET_AXIS = 0, CONST_AX, CONST_AY, CONST_ROT};

	constantConstraint(QString _name);
	~constantConstraint();

	void setConstantValue(double cv);
	void setTargetAxis(targetAXIS ta);

	virtual int constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul = 0);
	virtual void constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int i, bool isjp = false);
	virtual void derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i);
	virtual void lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1 = 0, double mul = 1);

private:
	double constant_value;
	targetAXIS target_axis;
};

#endif