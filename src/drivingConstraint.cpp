#include "drivingConstraint.h"
#include <QFile>
#include <QTextStream>

drivingConstraint::drivingConstraint(QString _name)
	: constraint(_name, DRIVING)
	, c_vel(0)
	, pos_0(0)
	, p_pos(0)
	, cs(NULL)
	, ct(NULL)
	, targetBody(0)

{
	constraint::nDimension += 1;
	constraint::nrow = 1;
	constraint::nnz = 1;
	constraint::nTotalNNZ += constraint::nnz;
	jrforce = new double;
}

drivingConstraint::~drivingConstraint()
{

}

void drivingConstraint::runFunction(double ct)
{

}

void drivingConstraint::setConstantVelocity(double _c_vel)
{
	c_vel = _c_vel;
}

void drivingConstraint::setTargetBody(rigidBody* _rb, coordinateType _ct)
{
	targetBody = _rb;
	ctype = _ct;
	unsigned int c1 = targetBody->ID() * 3;
	vecd3 pos = targetBody->Position();
	switch (ctype)
	{
	case AXIS_X: pos_0 = pos.X(); break;
	case AXIS_Y: pos_0 = pos.Y(); break;
	case AXIS_Z: pos_0 = pos.Z(); break;
	}
}

void drivingConstraint::bindGeneralizedCoordinate(VECD& q)
{
	unsigned int c1 = targetBody->ID() * 3;
	gp = &(q(c1 + static_cast<unsigned int>(ctype)));
}

void drivingConstraint::bindTime(double _dt, double* _ct, unsigned int* _cs)
{
	dt = _dt;
	ct = _ct;
	cs = _cs;
}

double drivingConstraint::ConstantVelocity()
{
	return c_vel;
}

void drivingConstraint::setPreviousPosition()
{
	p_pos = (*gp);
}

void drivingConstraint::constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul)
{
	if (velProfile.size())
	{
		double pv = (*cs) == 0 ? 0 : velProfile.at((*cs) - 1);
		double cv = velProfile.at((*cs));
		rhs(i) = (*gp) - p_pos - 0.5 * (pv + cv) * dt;
		c_vel = cv;
	}
	else
		rhs(i) = (*gp) - pos_0 - c_vel * (*ct);
}

void drivingConstraint::constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int r)
{
	unsigned int c1 = targetBody->ID() * 3;
	if (c1)
	{
		c1 -= 3;
		lhs(r, c1) = 1;
	}
}

void drivingConstraint::derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i)
{
	rhs(i) = 0.0;
}

void drivingConstraint::lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1, double mul)
{

}

void drivingConstraint::setVelocityProfile(QString _path)
{
	QFile qf(_path);
	qf.open(QIODevice::ReadOnly);
	QTextStream qts(&qf);
	double v = 0;
	while (!qts.atEnd())
	{
		qts >> v;
		velProfile.push_back(v);
	}
	qf.close();
}