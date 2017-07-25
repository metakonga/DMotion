#include "integrator.h"

integrator::integrator()
{

}

integrator::~integrator()
{

}

void integrator::calculatePositionFromVelocity(double p0, double dt, QVector<double> *vel, QVector<double> *pos)
{
	int n = vel->size();
	pos->push_back(p0);
	for (unsigned int i = 1; i < n; i++)
	{
		double o = pos->at(i - 1) + 0.5*(vel->at(i - 1) + vel->at(i)) * dt;
		pos->push_back(o);
	}
}