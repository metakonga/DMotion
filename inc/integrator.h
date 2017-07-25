#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <QVector>

class integrator
{
public:
	integrator();
	~integrator();

	void calculatePositionFromVelocity(double p0, double dt, QVector<double> *vel, QVector<double> *pos);
};

#endif