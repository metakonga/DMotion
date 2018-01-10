#ifndef REVOLUTEJOINT_H
#define REVOLUTEJOINT_H

#include "constraint.h"

class revoluteJoint : public constraint
{
public:
	revoluteJoint(QString _name);
	~revoluteJoint();

// 	void setBaseMarker(vecd3 q, vecd3 r);
// 	void setActionMarker(vecd3 q, vecd3 r);
	
	virtual int constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul = 0);
	virtual void constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int i, bool isjp = false);
	virtual void derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i);
	virtual void lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1 = 0, double mul = 1);
};

#endif