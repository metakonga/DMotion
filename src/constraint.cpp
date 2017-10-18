#include "constraint.h"

unsigned int constraint::nDimension = 0;
unsigned int constraint::nTotalNNZ = 0;

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
{

}

constraint::~constraint()
{
	if (jrforce) delete[] jrforce; jrforce = NULL;
}

void constraint::setActionBody(rigidBody *b)
{
	jb = b;
}

void constraint::setBaseBody(rigidBody *b)
{
	ib = b;
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