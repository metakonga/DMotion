#include "designConstraint.h"

designConstraint::designConstraint(QString _name)
	: name(_name)
{

}

designConstraint::~designConstraint()
{

}

void designConstraint::setComparisonTarget(compareTarget _ct)
{
	ct = _ct;
}
