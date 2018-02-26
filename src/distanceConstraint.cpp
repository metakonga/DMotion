#include "distanceConstraint.h"
#include "algebraMath.h"

distanceConstraint::distanceConstraint(QString _name)
	: designConstraint(_name)
{

}

distanceConstraint::~distanceConstraint()
{

}

void distanceConstraint::setTwoHardPoints(hardPoint* _p1, hardPoint* _p2)
{
	p1 = _p1;
	p2 = _p2;
}

void distanceConstraint::setConstraintValue(double base)
{
	value = base;
}

void distanceConstraint::setCheckLower()
{
	isCheckLower = true;
}

void distanceConstraint::setcheckUpper()
{
	isCheckLower = false;
}

bool distanceConstraint::checkConatraint()
{
	double dist = 0;
	switch (ct)
	{
	case DC_LENGTH: dist = math::length(p1->loc, p2->loc); break;
	case DC_VERTICAL: dist = abs(p2->loc.Y() - p1->loc.Y()); break;
	case DC_HORIZONTAL: dist = abs(p2->loc.X() - p1->loc.X()); break;
	}
	bool sts = false;
	if (isCheckLower) sts = dist < value;
	else sts = dist > value;
	return sts;
}