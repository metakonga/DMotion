#include "model.h"
#include <QList>
#include <QStandardItem>

model::model()
	: _isHasGroundModel(-1)
{
	
}

model::~model()
{
	qDeleteAll(bodies);
	qDeleteAll(cons);
	qDeleteAll(hardPoints);
	//qDeleteAll(bodyResultItems);
}

void model::setModelName(QString _modelName)
{
	modelName = _modelName;
}

QString model::ModelName()
{
	return modelName;
}

QVector<resultDataType>* model::bodyResultData(QString _name)
{
	QVectorIterator<rigidBody*> r(bodies);
	while (r.hasNext())
	{
		rigidBody* rb = r.next();
		if (_name == rb->Name())
			return rb->ResultData();
	}
	
	return NULL;
}

QVector<jointResultDataType>* model::jointResultData(QString _name)
{
	QVectorIterator<constraint*> c(cons);
	while (c.hasNext())
	{
		constraint* cs = c.next();
		if (_name == cs->Name())
			return cs->ResultData();
	}
	return NULL;
}

rigidBody* model::createRigidBody(QString _name)
{
	rigidBody *rb = new rigidBody(_name);
	bodies.push_back(rb);
	return rb;
}

revoluteJoint* model::createRevoluteJoint(QString _name)
{
	revoluteJoint* rev = new revoluteJoint(_name);
	cons.push_back(rev);
	return rev;
}

translateJoint* model::createTraslateJoint(QString _name)
{
	translateJoint* tra = new translateJoint(_name);
	cons.push_back(tra);
	return tra;
}

drivingConstraint* model::createDrivingConstraint(QString _name)
{
	drivingConstraint* dri = new drivingConstraint(_name);
	cons.push_back(dri);
	drivings.push_back(dri);
	return dri;
}

vecd3 model::getHalfBetween2HP(hardPoint* hpi, hardPoint* hpj)
{
	vecd3 p1 = hpi->loc;
	vecd3 p2 = hpj->loc;

	double x = p1.X() + 0.5 * (p2.X() - p1.X());
	double y = p1.Y() + 0.5 * (p2.Y() - p1.Y());
	double z = p1.Z() + 0.5 * (p2.Z() - p1.Z());
	return vecd3(x, y, z);
}

vecd3 model::getDiffBetween2HP(hardPoint* hpi, hardPoint* hpj)
{
	vecd3 p1 = hpi->loc;
	vecd3 p2 = hpj->loc;

	double x = p2.X() - p1.X();
	double y = p2.Y() - p1.Y();
	double z = p2.Z() - p1.Z();
	return vecd3(x, y, z);
}

double model::getLengthBetween2HP(hardPoint* hpi, hardPoint* hpj)
{
	vecd3 p1 = hpi->loc;
	vecd3 p2 = hpj->loc;
	double l = math::length(p1, p2);
	return l;
}

hardPoint* model::createHardPoint(QString _name, double x, double y, double z)
{
	hardPoint *hp = new hardPoint{ _name, vecd3(x, y, z) };
	hardPoints.push_back(hp);
	return hp;
}

double model::getAngleBetween2HP(hardPoint* hpi, hardPoint* hpj)
{
	double r;
	vecd3 diff = getDiffBetween2HP(hpi, hpj);
	r = atan(diff.Y() / diff.X());
	return r;
}

// hardPoint* model::getHardPoint(QString hp)
// {
// 	vecd3 r = hardPoints[hp];
// 	return r;
// }

QVector<rigidBody*>& model::RigidBodies()
{
	return bodies;
}

QVector<constraint*>& model::Constraints()
{
	return cons;
}

QVector<hardPoint*>& model::HardPoints()
{
	return hardPoints;
}

QVector<drivingConstraint*>& model::DrivingConstraints()
{
	return drivings;
}

unsigned int model::nBody()
{
	return bodies.size();
}

int model::hasGround()
{
	if (_isHasGroundModel != -1) 
		return _isHasGroundModel;
	foreach(rigidBody* v, bodies)
	{
		if (v->IsGround())
		{
			_isHasGroundModel = 1;
			return _isHasGroundModel;
		}			
	}
	_isHasGroundModel = 0;
	return _isHasGroundModel;
}