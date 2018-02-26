#ifndef DESIGNCONSTRAINT_H
#define DESIGNCONSTRAINT_H

#include "dmotion_types.h"

class designConstraint
{
public:
	enum compareTarget{ DC_LENGTH, DC_VERTICAL, DC_HORIZONTAL  };

	designConstraint(QString _name);
	~designConstraint();
	void setComparisonTarget(compareTarget _ct);
	virtual bool checkConatraint() = 0;

protected:
	compareTarget ct;

private:
	QString name;
};

#endif