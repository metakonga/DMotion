#ifndef DESIGNVARIABLE_H
#define DESIGNVARIABLE_H

#include <QString>
#include "dmotion_types.h"

class constraint;

class designVariable
{
public:
	designVariable(QString _name);
	~designVariable();

	void setCondition(double _lower, double _step, double _upper);
	void setDirection(coordinateType ct);
	void setConstraint(constraint* cs);
	bool updateVariable(bool _isFirst = false);
	void setEnable(bool _b);
	bool Enable();
	double Current();
	QString Name();
	void initializeCurrent();

private:
	bool isFirst;
	bool enable;
	QString name;
	coordinateType ctype;
	double current;
	double lower;
	double step;
	double upper;
	constraint* cons;
};

#endif