#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <QString>
#include "rigidBody.h"

typedef struct  
{
	vecd3 s;
	vecd3 actionAxis;
}joint_marker;

class constraint
{
public:
	constraint(QString _name, jointType _jtype);
	~constraint();

	void appendResultData(jointResultDataType jrdt);

	void setPosition(double x, double y, double z);
	void setBaseBody(rigidBody *b);
	void setActionBody(rigidBody *b);
	void setRowLocation(unsigned int _srow);
	void setDrivingConstraint(double(*_driving)(double));
	void bindHardPoint(hardPoint *_hp);

	void calcJointReactionForce(VECD& lm, unsigned int &sr);

	jointType JointType();
	unsigned int NNonZero();
	QString Name();
	QVector<jointResultDataType>* ResultData();
	hardPoint* BindedHardPoint();
	rigidBody* BaseBody();
	rigidBody* ActionBody();
	joint_marker& BaseMarker();
	joint_marker& ActionMarker();
	double* ReactionForce();
	static unsigned int NDimension();
	static unsigned int NTotalNonZero();

	virtual void constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul = 0) = 0;
	virtual void constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int i) = 0;
	virtual void derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i) = 0;
	virtual void lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1 = 0, double mul = 1) = 0;

protected:
	static unsigned int nDimension;
	static unsigned int nTotalNNZ;
	double *jrforce;
	unsigned int nnz;
	unsigned int nrow;
	unsigned int srow;
	jointType jtype;
	QString name;
	vecd3 pos;
	joint_marker baseMarker;
	joint_marker actionMarker;
	rigidBody *ib;
	rigidBody *jb;
	hardPoint *hp;
	QVector<jointResultDataType> results;
};

#endif