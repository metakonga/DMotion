#include "model.h"
#include <QList>
#include <QDir>
#include <QStandardItem>
#include <QDebug>
#include <QTextStream>

model::model(modelType mt)
	: _isHasGroundModel(-1)
	, nCoordinates(0)
	, pfollower(NULL)
	, noSatisfiedCamAngle(0)
	, cam_angle_lower(0)
	, cam_angle_upper(0)
	, mtype(mt)
{
	
}

model::~model()
{
	qDeleteAll(bodies); bodies.clear();
	qDeleteAll(cons); cons.clear();
	qDeleteAll(hardPoints); hardPoints.clear();
	qDeleteAll(designs); designs.clear();
	if (pfollower) delete pfollower; pfollower = NULL;
}

void model::setCoordinateNumber(unsigned int nc)
{
	nCoordinates = nc;
}

void model::setCamAngleDesignVariable(double lo, double up)
{
	cam_angle_lower = lo;
	cam_angle_upper = up;
}

void model::setCamAngleDesignVariableEnable(bool b)
{
	cam_angle_enable = b;
}

void model::setModelName(QString _modelName)
{
	modelName = _modelName;
}

void model::setModelPath(QString _modelPath)
{
	modelPath = _modelPath + modelName + "/";
	if (!QDir(modelPath).exists())
		QDir().mkdir(modelPath);
}

QString model::ModelName()
{
	return modelName;
}

QString model::ModelPath()
{
	return modelPath;
}

QVector<resultDataType>* model::bodyResultData(QString _name)
{
	QMapIterator<QString, rigidBody*> r(bodies);
	while (r.hasNext())
	{
		rigidBody* rb = r.next().value();
		if (_name == rb->Name())
			return rb->ResultData();
	}
	
	return NULL;
}

QVector<jointResultDataType>* model::jointResultData(QString _name)
{
	QMapIterator<QString, constraint*> c(cons);
	while (c.hasNext())
	{
		constraint* cs = c.next().value();
		if (_name == cs->Name())
			return cs->ResultData();
	}
	return NULL;
}

rigidBody* model::createRigidBody(QString _name)
{
	rigidBody *rb = new rigidBody(_name);
	bodies[_name] = rb;/// bodies.push_back(rb);]
	return rb;
}

revoluteJoint* model::createRevoluteJoint(QString _name)
{
	revoluteJoint* rev = new revoluteJoint(_name);
	cons[_name] = rev;// cons.push_back(rev);
	return rev;
}

translateJoint* model::createTraslateJoint(QString _name)
{
	translateJoint* tra = new translateJoint(_name);
	cons[_name] = tra;// cons.push_back(tra);
	return tra;
}

drivingConstraint* model::createDrivingConstraint(QString _name)
{
	drivingConstraint* dri = new drivingConstraint(_name);
	cons[_name] = dri;// cons.push_back(dri);
	drivings[_name] = dri;// drivings.push_back(dri);
	return dri;
}

constantConstraint* model::createConstantConstraint(QString _name)
{
	constantConstraint* c = new constantConstraint(_name);
	cons[_name] = c;
	return c;
}

designVariable* model::createDesignVariable(QString _name)
{
	designVariable* dv = new designVariable(_name);
	designs[_name] = dv;
	return dv;
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
	hardPoint *hp = new hardPoint{ _name, vecd3(x,y,z), vecd3(x, y, z) };
	hardPoints[_name] = hp;
	return hp;
}

pointFollower* model::createPointFollower(QString _name)
{
	pfollower = new pointFollower(_name);
	return pfollower;
}

double model::getAngleBetween2HP(hardPoint* hpi, hardPoint* hpj)
{
	double r;
	vecd3 diff = getDiffBetween2HP(hpi, hpj);
	r = atan(diff.Y() / diff.X());
	return r;
}

QList<QString>& model::BodyList()
{
	return bodyList;
}

QList<QString>& model::ConstraintList()
{
	return constList;
}

QMap<QString, rigidBody*>& model::RigidBodies()
{
	return bodies;
}

QMap<QString, constraint*>& model::Constraints()
{
	return cons;
}

QMap<QString, hardPoint*>& model::HardPoints()
{
	return hardPoints;
}

QMap<QString, drivingConstraint*>& model::DrivingConstraints()
{
	return drivings;
}

QMap<QString, designVariable*>& model::DesignVariables()
{
	return designs;
}

QMap<int, reactionForceType>& model::ReactionMap()
{
	return reactionMap;
}

modelType model::ModelType()
{
	return mtype;
}

pointFollower* model::PointFollower()
{
	return pfollower;
}

QList<QString>& model::HardPointList()
{
	return hpList;
}

unsigned int model::nBody()
{
	return bodies.size();
}

verticalConstraint* model::createVerticalConstraint(QString _name)
{
	verticalConstraint* con = new verticalConstraint(_name);
	cons[_name] = con;
	return con;
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

void model::setGeneralizedCoordinate(unsigned int step, VECD& q, VECD& qd, VECD& qdd)
{
	unsigned int i = 0;
	foreach(QString str, bodyList)
	{
		rigidBody *rb = bodies[str];
		resultDataType rdt = rb->getResult(step);
		q(i) = rdt.pos.X(); q(i + 1) = rdt.pos.Y(); q(i + 2) = rdt.ang;
		qd(i) = rdt.vel.X(); qd(i + 1) = rdt.vel.Y(); qd(i + 2) = rdt.angv;
		qdd(i) = rdt.acc.X(); qdd(i + 1) = rdt.acc.Y(); qdd(i + 2) = rdt.anga;
		i += 3;
	}
}

bool model::updateDesignVariable(QString &hps, bool isFirst)
{
	bool isOver = true;
	isEmptyEnableDesignVariable = true;
	QTextStream qts(&hps);

	foreach(designVariable* dv, designs)
	{
		if (!dv->Enable())
			continue;
		isEmptyEnableDesignVariable = false;
		bool isEnd = dv->updateVariable(isFirst);

		if (!isEnd)
		{
			isOver = false;
			break;
		}
		else
		{
			//dv->initializeCurrent();
		}
	}
	if (isEmptyEnableDesignVariable)
	{
		return true;
	}
	qts << "| ";
	foreach(designVariable* dv, designs)
	{
		if (!dv->Enable())
			continue;
		qts << dv->Name() << " : " << dv->Current() << " | ";
	}
	foreach(rigidBody *rb, bodies)
	{
		// 		if (rb->IsGround())
		// 			continue;
		rb->initializeBody();
	}

	rigidBody* rb = bodies["Nozzle"];
	hardPoint* hp = hardPoints["active_link"];
	vecd3 dif = hp->loc - hp->loc0;
	rb->setPosition(rb->Position().X() + dif.X(), rb->Position().Y() + dif.Y(), 0.0);

	rigidBody* rb1 = bodies["Link"];
	hardPoint* hp1 = hardPoints["link_cam"];
	vecd3 r0 = rb1->Position0();
	vecd3 len = hp->loc0 - r0;
	vecd3 tlen = hp->loc0 - hp1->loc0;
	vecd3 rate = vecd3(len.X() / tlen.X(), len.Y() / tlen.Y(), 0.0);
	vecd3 cur_dif = hp1->loc - hp->loc;
	//double cur_len = math::length(cur_dif);
	//vecd3 u = vecd3(cur_dif.X() / cur_len, cur_dif.Y() / cur_len, 0.0);
	vecd3 new_pos = vecd3(cur_dif.X() * rate.X(), cur_dif.Y() * rate.Y(), 0.0);
	rb1->setPosition(hp->loc.X() + new_pos.X(), hp->loc.Y() + new_pos.Y(), 0.0);

	foreach(constraint *cs, cons)
	{
		if (cs->JointType() == DRIVING)
			continue;

		cs->initializeConstraint();
	}
	foreach(drivingConstraint *dc, drivings)
	{
		dc->initializeDrivingPosition();
	}
	if (pfollower)
	{
		vecd3 hp0 = hardPoints["cam_ground"]->loc;
		vecd3 hp1 = hardPoints["cam_passive"]->loc;
		pfollower->initialize(hp0, hp1);
// 		pfollower->setActionHardPoint(hp0);
// 		vecd3 dp = hp1 - hp0;
// 		double len = math::length(dp);
// 		double ang = acos(dp.X() / len);
// 		if (dp.Y() < 0)
// 			ang = M_PI + (M_PI - ang);
// 		pfollower->setInitialAngle(ang);
// 		pfollower->initializeCurveData();
// 		pfollower->setCM2HardPoint();
// 		pfollower->updateBaseMarker();
	}
	if (isEmptyEnableDesignVariable)
		isOver = false;
	if (cam_angle_enable)
	{
		vecd3 hp0 = hardPoints["link_cam"]->loc;
		vecd3 hp1 = hardPoints["cam_ground"]->loc;
		vecd3 dp = hp0 - hp1;
		double len = math::length(dp);
		double ang = (180 / M_PI) * (acos(-dp.Y() / len));
		//qDebug() << "cam angle : " << ang;
		if (ang > cam_angle_lower && ang < cam_angle_upper)
		{
			isSatisfyCamAngle = true;
			noSatisfiedCamAngle = 0.0;
		}
		else
		{
			isSatisfyCamAngle = false;
			noSatisfiedCamAngle = ang;
		}
	}
	
	return isOver;
}

bool model::IsEmptyEnableDesignVariable()
{
	return isEmptyEnableDesignVariable;
}

bool model::IsSatisfyCamAngle()
{
	return isSatisfyCamAngle;
}

void model::initializeDesignVariable()
{
// 	rigidBody* rb = bodies["active"];
// 	hardPoint* hp = hardPoints["active_link"];
// 	vecd3 dif = hp->loc0 - hp->loc;
// 	rb->setPosition(rb->Position().X() + dif.X(), rb->Position().Y() + dif.Y(), 0.0);
// 
// 	rb = bodies["link"];
// 	hardPoint* hp1 = hardPoints["link_cam"];
// 	vecd3 r0 = rb->Position0();
// 	vecd3 len = hp->loc0 - r0;
// 	vecd3 tlen = hp->loc0 - hp1->loc0;
// 	vecd3 rate = vecd3(len.X() / tlen.X(), len.Y() / tlen.Y(), 0.0);
// 	vecd3 cur_dif = hp1->loc - hp->loc;
// 	//double cur_len = math::length(cur_dif);
// 	//vecd3 u = vecd3(cur_dif.X() / cur_len, cur_dif.Y() / cur_len, 0.0);
// 	vecd3 new_pos = vecd3(cur_dif.X() * rate.X(), cur_dif.Y() * rate.Y(), 0.0);
	foreach(designVariable* dv, designs)
	{
		if (!dv->Enable())
			continue;
		dv->initializeCurrent();
	}
}

double model::NoSatisfiedCamAngle()
{
	return noSatisfiedCamAngle;
}

// reactionForceType model::Constraint2ReactionType(QString _name, coordinateType ctype)
// {
// 	if ()
// }
