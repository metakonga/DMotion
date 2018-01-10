#include "constantConstraint.h"

constantConstraint::constantConstraint(QString _name)
	: constraint(_name, CONSTANT)
	, constant_value(0)
	, target_axis(TARGET_AXIS)
{
	constraint::nDimension += 1;
	constraint::nrow = 1;
	constraint::nnz = 1;
	constraint::nTotalNNZ += constraint::nnz;
	jrforce = new double[constraint::nrow];
}

constantConstraint::~constantConstraint()
{

}

void constantConstraint::setTargetAxis(targetAXIS ta)
{
	target_axis = ta;
}

void constantConstraint::setConstantValue(double cv)
{
	constant_value = cv;
}

void constantConstraint::constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int r, bool isjp)
{
	unsigned int ci = ib->ID() * 3 - 3;
	switch (target_axis)
	{
	case CONST_AX: lhs(r, ci) = 1; break;
	case CONST_AY: lhs(r, ci + 1) = 1; break;
	case CONST_ROT: lhs(r, ci + 2) = 1; break;
	default:
		break;
	}
}

int constantConstraint::constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul)
{
	unsigned int ci = ib->ID() * 3;
	double target_value;
	switch (target_axis)
	{
	case CONST_AX: target_value = q(ci); break;
	case CONST_AY: target_value = q(ci + 1); break;
	case CONST_ROT: target_value = q(ci + 2); break;
	default:
		break;
	}

	rhs(i) = mul * (target_value - constant_value);
	return 0;
}

void constantConstraint::derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i)
{

}

void constantConstraint::lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1, double mul)
{

}