#include "optimumCase.h"

optimumCase::optimumCase(QString _name)
	: name(_name)
	, count(0)
	, maxArea(0)
{

}

optimumCase::~optimumCase()
{
	bodyResults.clear();
	reactionResults.clear();
	maximumReaction.clear();
	camProfileResults.clear();
	hardPointResults.clear();
}

stMaxReaction& optimumCase::maxReactionStructure(reactionForceType _type)
{
	return maximumReaction[_type];
}

QMap<reactionForceType, stMaxReaction>& optimumCase::MaximumReactions()
{
	return maximumReaction;
}

QMap<QString, QVector<resultDataType>>& optimumCase::BodyResults()
{
	return bodyResults;
}

QMap<QString, QVector<jointResultDataType>>& optimumCase::ReactionResults()
{
	return reactionResults;
}

QMap<QString, QVector<vecd3>>& optimumCase::HardPointsResults()
{
	return hardPointResults;
}

QVector<QPointF>& optimumCase::CamProfileResults()
{
	return camProfileResults;
}

QString optimumCase::Name()
{
	return name;
}

void optimumCase::appendBodyResults(model* md, double ct, VECD& q, VECD& qd, VECD& qdd)
{
	unsigned int i = 0;
	foreach(QString str, md->BodyList())
	{
		rigidBody* rb = md->RigidBodies()[str];
		resultDataType rdt;
		rdt.time = ct;
		rdt.pos = vecd3(q(i), q(i + 1), 0);
		rdt.vel = vecd3(qd(i), qd(i + 1), 0);
		rdt.acc = vecd3(qdd(i), qdd(i + 1), 0);
		rdt.ang = q(i + 2);
		rdt.angv = qd(i + 2);
		rdt.anga = qdd(i + 2);
		bodyResults[str].push_back(rdt);
// 		rb->setPosition(q(i), q(i + 1), 0);
// 		rb->setVelocity(qd(i), qd(i + 1), 0);
// 		rb->setAcceleration(qdd(i), qdd(i + 1), 0);
// 		rb->setAngle(q(i + 2));
// 		rb->setAngularVelocity(qd(i + 2));
// 		rb->setAngularAcceleration(qdd(i + 2));
// 		rb->appendResultData(rdt);
		i += 3;
	}
}

void optimumCase::appendReactionResults(model* md, double ct)
{
	double unit = 1 / 9.80665;
	stMaxReaction mr0 = { 0, };
	stMaxReaction mr1 = { 0, };
	double abx = 0.0;
	double aby = 0.0;
	reactionForceType rft;
	foreach(constraint* cs, md->Constraints())
	{
		jointResultDataType jrdt = { 0, };
		jrdt.time = ct;
		switch (cs->JointType())
		{
		case REVOLUTE:
			jrdt.fx = -cs->ReactionForce()[0] * unit;
			jrdt.fy = -cs->ReactionForce()[1] * unit;
			jrdt.fm = sqrt(jrdt.fx * jrdt.fx + jrdt.fy * jrdt.fy);
			rft = cs->ReactionForceType1();
			mr0 = maximumReaction[rft];
			abx = abs(jrdt.fx);
			aby = abs(jrdt.fy);

			if (mr0.maximum < abx)
			{
				mr0.maximum = abx;
				mr0.dir = "FX";
				mr0.time = ct;
				maximumReaction[rft] = mr0;
			}
			rft = cs->ReactionForceType2();
			mr1 = maximumReaction[rft];
			if (mr1.maximum < aby)
			{
				mr1.maximum = aby;
				mr1.dir = "FY";
				mr1.time = ct;
				maximumReaction[rft] = mr1;
			}
			
			break;
		case TRANSLATION:
			jrdt.fx = -cs->ReactionForce()[0] * unit;
			jrdt.fy = -cs->ReactionForce()[1] * unit / 1000.0;
			jrdt.fm = sqrt(jrdt.fx * jrdt.fx + jrdt.fy * jrdt.fy);
			rft = cs->ReactionForceType1();
			mr0 = maximumReaction[rft];
			abx = abs(jrdt.fx);
			aby = abs(jrdt.fy);
			if (mr0.maximum < abx)
			{
				mr0.maximum = abx;
				mr0.dir = "FY";
				mr0.time = ct;
				maximumReaction[rft] = mr0;
			}
			rft = cs->ReactionForceType2();
			mr1 = maximumReaction[rft];
			if (mr1.maximum < aby)
			{
				mr1.maximum = aby;
				mr1.dir = "TR";
				mr1.time = ct;
				maximumReaction[rft] = mr1;
			}
			break;
		case DRIVING:
// 			jrdt.fx = -cs->ReactionForce()[0];
// 			mr0 = maximumReaction[cs->Name() + "_FX"];
// 			abx = abs(jrdt.fx);
// 			if (mr0.maximum < abx)
// 			{
// 				mr0.maximum = abx;
// 				mr0.dir = "FD";
// 				mr0.time = ct;
// 				maximumReaction[cs->Name() + "_FX"] = mr0;
// 			}
			
			break;
		}
		reactionResults[cs->Name()].push_back(jrdt);
// 		unsigned int b_id = cs->BaseBody()->ID() * 3;
// 		vecd3 b_loc_pos = cs->BaseMarker().s;
// 		vecd3 i_pos(q(b_id), q(b_id + 1), 0.0);
// 		transformationMatrix A = TM(q(b_id + 2));
// 		jrdt.loc = i_pos + math::local2global(A, b_loc_pos);
		//cs->appendResultData(jrdt);
	}
	jointResultDataType jrdt = { 0, };
	jrdt.time = ct;
	pointFollower *pf = md->PointFollower();// ()["cam_profile"];
	jrdt.fx = pf->ReactionForce()[0] * unit;
	jrdt.fy = pf->ReactionForce()[1] * unit;
	jrdt.fm = 0.0;
	//jrdt.loc = vecd3(0.0, 0.0, 0.0);
	rft = pf->ReactionForceType1();
	mr0 = maximumReaction[rft];
	abx = abs(jrdt.fx);
	aby = abs(jrdt.fy);
	if (mr0.maximum < abx)
	{
		mr0.maximum = abx;
		mr0.dir = "FX";
		mr0.time = ct;
		maximumReaction[rft] = mr0;
	}
	rft = pf->ReactionForceType2();
	mr1 = maximumReaction[rft];
	if (mr1.maximum < aby)
	{
		mr1.maximum = aby;
		mr1.dir = "FY";
		mr1.time = ct;
		maximumReaction[rft] = mr1;
	}
	
	reactionResults[pf->Name()].push_back(jrdt);
}

void optimumCase::appendHardPointResult(model* md, double ct)
{
	foreach(constraint* cs, md->Constraints())
	{
		if (cs->JointType() == DRIVING)
			continue;
		if (cs->JointType() == TRANSLATION)
			continue;
		vecd3 loc = cs->calcJointLocation();
		hardPointResults[cs->BindedHardPoint()->name].push_back(loc);
	}
	pointFollower* pf = md->PointFollower();
	vecd3 loc = pf->calcJointLocation();
	hardPointResults[pf->BindedHardPoint()->name].push_back(loc);
}

void optimumCase::appendCamProfileResult(pointFollower* pf, double ct)
{
	camProfileResults = pf->ProfileData();
	maxArea = pf->MaxDistance();
}

void optimumCase::setResultCount(unsigned int nc)
{
	count = nc;
}

unsigned int optimumCase::ResultCount()
{
	return count;
}

double optimumCase::MaxAreaRange()
{
	return maxArea;
}

void optimumCase::saveCase(QFile& stream, unsigned int idx)
{
	stream.write((char*)&idx, sizeof(unsigned int));
	QMapIterator<QString, QVector<resultDataType>> rbody(bodyResults);
	int sz = 0;
	while (rbody.hasNext())
	{
		rbody.next();
		sz = rbody.key().size();
		stream.write((char*)&sz, sizeof(int));
		stream.write((char*)rbody.key().data(), sizeof(QChar) * rbody.key().size());
		stream.write((char*)rbody.value().data(), sizeof(resultDataType) * rbody.value().size());
	}
	QMapIterator<QString, QVector<jointResultDataType>> react(reactionResults);
	while (react.hasNext())
	{
		react.next();
		sz = react.key().size();
		stream.write((char*)&sz, sizeof(int));
		stream.write((char*)react.key().data(), sizeof(QChar) * react.key().size());
		stream.write((char*)react.value().data(), sizeof(jointResultDataType) * react.value().size());
	}
	QMapIterator<QString, QVector<vecd3>> hps(hardPointResults);
	while (hps.hasNext())
	{
		hps.next();
		sz = react.key().size();
		stream.write((char*)&sz, sizeof(int));
		stream.write((char*)hps.key().data(), sizeof(QChar) * react.key().size());
		stream.write((char*)hps.value().data(), sizeof(vecd3) * hps.value().size());
	}
	QMapIterator<reactionForceType, stMaxReaction> maxReact(maximumReaction);
	while (maxReact.hasNext())
	{
		maxReact.next();
		/*sz = maxReact.key().size();*/
		int rft = (int)maxReact.key();
		//stream.write((char*)&, sizeof(int));
		stream.write((char*)&rft, sizeof(int));
		stream.write((char*)&maxReact.value(), sizeof(stMaxReaction));
	}
	QString ch = "camProfile";
	sz = ch.size();
	stream.write((char*)&sz, sizeof(int));
	stream.write((char*)ch.data(), sizeof(QChar) * ch.size());
	stream.write((char*)camProfileResults.data(), sizeof(QPointF) * camProfileResults.size());
}

