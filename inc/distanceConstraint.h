#ifndef DISTANCECONSTRAINT_H
#define DISTANCECONSTRAINT_H

#include "designConstraint.h"


class distanceConstraint : public designConstraint
{
public:
	distanceConstraint(QString _name);
	virtual ~distanceConstraint();

	void setTwoHardPoints(hardPoint* p1, hardPoint* p2);
	void setConstraintValue(double base);
	void setCheckLower();
	void setcheckUpper();
	

	virtual bool checkConatraint();

private:
	bool isCheckLower;
	double value;

	hardPoint* p1;
	hardPoint* p2;
};

#endif