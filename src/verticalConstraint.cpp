#include "verticalConstraint.h"

verticalConstraint::verticalConstraint(QString _name)
	: constraint(_name, VERTICAL)
{
	constraint::nDimension += 1;
	constraint::nrow = 1;
	constraint::nnz = 4;
	constraint::nTotalNNZ += constraint::nnz;
	jrforce = new double[constraint::nrow];
}

verticalConstraint::~verticalConstraint()
{

}

void verticalConstraint::defineInitialVerticalValue(double _y)
{
	ivalue = _y;
}

int verticalConstraint::constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul)
{
	unsigned int ci = ib->ID() * 3;
	rhs(i) = mul * (q(ci + 2) - 0.0);
	return 0;
}

void verticalConstraint::constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int r, bool isjp)
{
	unsigned int ci = ib->ID() * 3 - 3;
	lhs(r, ci + 2) = 1;
}

void verticalConstraint::derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i)
{

}

void verticalConstraint::lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1, double mul)
{

}