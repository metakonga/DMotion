#include "designVariable.h"
#include "constraint.h"

designVariable::designVariable(QString _name)
	: name(_name)
	, cons(NULL)
	, isFirst(true)
	, current(0)
	, lower(0)
	, step(0)
	, upper(0)
{

}

designVariable::~designVariable()
{

}

void designVariable::setCondition(double _lower, double _step, double _upper)
{
	//enable = true;
	lower = _lower;
	step = _step;
	upper = _upper;
	current = lower;
}

void designVariable::setDirection(coordinateType ct)
{
	ctype = ct;
}

void designVariable::setConstraint(constraint* cs)
{
	cons = cs;
}

bool designVariable::updateVariable(bool _isFirst)
{
	if (_isFirst)
	{
		//cons->updatePosition(ctype, current);
		isFirst = false;
		return false;
	}
	current = current + step;
	if (current > upper + 1e-9)
	{
		current = lower;
		cons->updatePosition(ctype, -(upper - lower));
		return true;
	}
	else
	{
		
		cons->updatePosition(ctype, step);
	}
	return false;
}

void designVariable::setEnable(bool _b)
{
	enable = _b;
}

bool designVariable::Enable()
{
	return enable;
}

double designVariable::Current()
{
	return current;
}

QString designVariable::Name()
{
	return name;
}

void designVariable::initializeCurrent()
{
	//isFirst = true;
	cons->updatePosition(ctype, lower);
}
