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
	memset(jrforce, 0, sizeof(double) * constraint::nrow);
}

drivingConstraint::~drivingConstraint()
{
	velProfile.clear();
	dvelProfile.clear();
	ddvelProfile.clear();
}

void drivingConstraint::runFunction(double ct)
{

}

double drivingConstraint::MaxVelocityTime()
{
	return maxTime;
}

double drivingConstraint::MaxVelocity()
{
	return maxAbsVel;
}

QString drivingConstraint::FilePath()
{
	return file;
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

QVector<double>& drivingConstraint::VelocityProfile()
{
	return velProfile;
}

QPointF drivingConstraint::TimeVelocity(int idx)
{
	return QPointF(time.at(idx), velProfile.at(idx));
}

double drivingConstraint::ConstantVelocity()
{
	return c_vel;
}

void drivingConstraint::initializeDrivingPosition()
{
	vecd3 pos = targetBody->Position();
	switch (ctype)
	{
	case AXIS_X: p_pos = pos.X(); break;
	case AXIS_Y: p_pos = pos.Y(); break;
	case AXIS_Z: p_pos = pos.Z(); break;
	}
}

void drivingConstraint::setPreviousPosition()
{
	p_pos = (*gp);
}

int drivingConstraint::constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul)
{
	if (velProfile.size())
	{
		if ((*cs) == velProfile.size())
		{
			return -1;
		}
		double pv = (*cs) == 0 ? 0 : velProfile.at((*cs) - 1);
		double cv = velProfile.at((*cs));
		rhs(i) = (*gp) - p_pos - 0.5 * (pv + cv) * dt;
		c_vel = cv;
	}
	else
		rhs(i) = (*gp) - pos_0 - c_vel * (*ct);
	return 0;
}

void drivingConstraint::constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int r, bool isjp)
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
	rhs(i) = dvelProfile.at(*cs);
}

void drivingConstraint::lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1, double mul)
{

}

bool drivingConstraint::setVelocityProfile(QString _path)
{
	QFile qf(_path);
	qf.open(QIODevice::ReadOnly);
	if (!qf.isOpen())
		return false;
	QTextStream qts(&qf);
	double v = 0;
	double t = 0;
	maxAbsVel = 0;
	maxTime = 0;
	if (velProfile.size())
		velProfile.clear();

	while (!qts.atEnd())
	{
		qts >> t >> v;
		if (abs(v) > maxAbsVel)
		{
			maxTime = t;
			maxAbsVel = abs(v);
		}			
		time.append(t);
		velProfile.append(v);
		//t += 0.00001;
	}
	if (dvelProfile.size())
		dvelProfile.clear();
	if (ddvelProfile.size())
		ddvelProfile.clear();
	dvelProfile.push_back(0);
	ddvelProfile.push_back(0);
	for (unsigned int i = 1; i < velProfile.size() - 1; i++)
	{
		double pv = velProfile.at(i - 1);
		double nv = velProfile.at(i + 1);
		double cv = 0.5 * (nv - pv) / 0.00001;
		dvelProfile.push_back(cv);
	}
	dvelProfile.push_back(0);
	for (unsigned int i = 1; i < velProfile.size() - 1; i++)
	{
		double pv = dvelProfile.at(i - 1);
		double nv = dvelProfile.at(i + 1);
		double cv = 0.5 * (nv - pv) / 0.00001;
		ddvelProfile.push_back(cv);
	}
	ddvelProfile.push_back(0);
 	qf.close();
	file = _path;
	return true;
}