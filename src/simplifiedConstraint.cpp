#include "simplifiedConstraint.h"

simplifiedConstraint::simplifiedConstraint(QString _name)
	: constraint(_name, SIMPLIFIED)
{
	constraint::nDimension += 1;
	constraint::nrow = 1;
	constraint::nnz = 4;
	constraint::nTotalNNZ += constraint::nnz;
	jrforce = new double[constraint::nrow];
}

simplifiedConstraint::~simplifiedConstraint()
{

}

void simplifiedConstraint::setConstantValue(double _y)
{
	ivalue = _y;
}

void simplifiedConstraint::setConstantValueFromBaseBody()
{
	if (hp)
		ivalue = direction == VERTICAL ? hp->loc.Y() : (direction == HORIZONTAL ? hp->loc.X() : 0);
	else
		ivalue = direction == VERTICAL ? ib->Position().Y() : (direction == HORIZONTAL ? ib->Position().X() : ib->Angle());
}

void simplifiedConstraint::setPositionFromHardPoint()
{
	if (hp)
		pos = hp->loc;
}

void simplifiedConstraint::setDirection(DRIECTION _direction)
{
	direction = _direction;
}

simplifiedConstraint::DRIECTION simplifiedConstraint::Direction()
{
	return direction;
}

int simplifiedConstraint::constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul)
{
	unsigned int ci = ib->ID() * 3;
	double cvalue = 0;
	double ang = q(ci + 2);
	if (direction == HORIZONTAL)
		cvalue = cos(ang) * baseMarker.s.X() - sin(ang)*baseMarker.s.Y();
	else if (direction == VERTICAL)
		cvalue = sin(ang) * baseMarker.s.X() + cos(ang)*baseMarker.s.Y();
	else if (direction == ROTATION)
		cvalue = ivalue;

	rhs(i) = mul * (q(ci + int(direction)) + cvalue - ivalue);
	return 0;
}

void simplifiedConstraint::constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int r, bool isjp)
{
	unsigned int ci = ib->ID() * 3 - 3;
	lhs(r, ci + int(direction)) = 1;
}

void simplifiedConstraint::derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i)
{

}

void simplifiedConstraint::lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1, double mul)
{

}