#include "constraint.h"

unsigned int constraint::nDimension = 0;
unsigned int constraint::nTotalNNZ = 0;
unsigned int constraint::s_step = 0;
bool constraint::ignoreAllOptions = false;

constraint::constraint(QString _name, jointType _jtype)
	: name(_name)
	, jtype(_jtype)
	, jrforce(NULL)
	, nrow(0)
	, srow(0)
	, nnz(0)
	, hp(NULL)
	, ib(NULL)
	, jb(NULL)
	, isFixedWhenKinematicAnalysis(false)
{

}

constraint::~constraint()
{
	if (jrforce) delete[] jrforce; jrforce = NULL;
}

void constraint::setSolverStep(unsigned int ss)
{
	s_step = ss;
}

bool constraint::IsFixedWhenKinematicAnalysis()
{
	return isFixedWhenKinematicAnalysis;
}

void constraint::setActionBody(rigidBody *b)
{
	jb = b;
}

void constraint::setBaseBody(rigidBody *b)
{
	ib = b;
}

void constraint::setBaseMarker(vecd3 q, vecd3 r)
{
	baseMarker.s = math::global2local(ib->TM(), pos - ib->Position());
	baseMarker.actionAxis = math::cross(q, r);
}

void constraint::setActionMarker(vecd3 q, vecd3 r)
{
	actionMarker.s = math::global2local(jb->TM(), pos - jb->Position());
	actionMarker.actionAxis = math::cross(q, r);
}

void constraint::setReactionForceTypes(reactionForceType r1, reactionForceType r2)
{
	rft1 = r1;
	rft2 = r2;
}

void constraint::setFixedWhelKinematicAnalysis(bool b)
{
	isFixedWhenKinematicAnalysis = b;
	constraint::nDimension += 1;
}

void constraint::setPosition(double x, double y, double z)
{
	pos = vecd3(x, y, z);
}

jointType constraint::JointType()
{
	return jtype;
}

unsigned int constraint::NDimension()
{
	return nDimension;
}

unsigned int constraint::NTotalNonZero()
{
	return nTotalNNZ;
}

void constraint::setIgnoreAllOptions(bool b)
{
	ignoreAllOptions = b;
}

void constraint::calcJointReactionForce(VECD& _lm, unsigned int &sr)
{
	if (jtype == REVOLUTE)
		for (unsigned int i = 0; i < nrow; i++)
			jrforce[i] = _lm(sr++);
	else if (jtype == TRANSLATION)
		for (unsigned int i = 0; i < nrow; i++)
			jrforce[i] = _lm(sr++);
	else if (jtype == DRIVING)
		jrforce[0] = _lm(sr++);
	else if (jtype == POINTFOLLOWER)
		for (unsigned int i = 0; i < nrow; i++)
			jrforce[i] = _lm(sr++);
	else if (jtype == SIMPLIFIED)
		jrforce[0] = _lm(sr++);
}

void constraint::initializeConstraint()
{
	if(ib) baseMarker.s = math::global2local(ib->TM(), pos - ib->Position());
	if(jb) actionMarker.s = math::global2local(jb->TM(), pos - jb->Position());
	memset(jrforce, 0, sizeof(double) * constraint::nrow);
}

void constraint::setRowLocation(unsigned int _srow)
{
	srow = _srow;
}

unsigned int constraint::NNonZero()
{
	return nnz;
}

QString constraint::Name()
{
	return name;
}

unsigned int constraint::NRow()
{
	return nrow;
}

void constraint::appendResultData(jointResultDataType jrdt)
{
	results.push_back(jrdt);
}

QVector<jointResultDataType>* constraint::ResultData()
{
	return &results;
}

void constraint::bindHardPoint(hardPoint *_hp)
{
	hp = _hp;
}

hardPoint* constraint::BindedHardPoint()
{
	return hp;
}

rigidBody* constraint::BaseBody()
{
	return ib;
}

rigidBody* constraint::ActionBody()
{
	return jb;
}

joint_marker& constraint::BaseMarker()
{
	return baseMarker;
}

joint_marker& constraint::ActionMarker()
{
	return actionMarker;
}

double* constraint::ReactionForce()
{
	return jrforce;
}

reactionForceType constraint::ReactionForceType1()
{
	return rft1;
}

reactionForceType constraint::ReactionForceType2()
{
	return rft2;
}

void constraint::updatePosition(coordinateType ct, double dv)
{
	switch (ct)
	{
	case AXIS_X: pos.SetX(pos.X() + dv); break;
	case AXIS_Y: pos.SetY(pos.Y() + dv); break;
	}
	hp->loc = pos;
}

vecd3 constraint::calcJointLocation()
{
	vecd3 loc = ib->Position() + math::local2global(ib->TM(), baseMarker.s);
	return loc;
}
