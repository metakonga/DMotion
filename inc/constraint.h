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
	virtual ~constraint();

	void appendResultData(jointResultDataType jrdt);

	void setPosition(double x, double y, double z);
	void setBaseBody(rigidBody *b);
	void setActionBody(rigidBody *b);
	void setRowLocation(unsigned int _srow);
	void setDrivingConstraint(double(*_driving)(double));
	void setBaseMarker(vecd3 q, vecd3 r);
	void setActionMarker(vecd3 q, vecd3 r);
	void setReactionForceTypes(reactionForceType r1, reactionForceType r2);
	void setFixedWhelKinematicAnalysis(bool b);
	void bindHardPoint(hardPoint *_hp);

	void calcJointReactionForce(VECD& lm, unsigned int &sr);
	void initializeConstraint();
	vecd3 calcJointLocation();
	jointType JointType();
	unsigned int NNonZero();
	unsigned int NRow();
	QString Name();
	QVector<jointResultDataType>* ResultData();
	hardPoint* BindedHardPoint();
	rigidBody* BaseBody();
	rigidBody* ActionBody();
	joint_marker& BaseMarker();
	joint_marker& ActionMarker();
	double* ReactionForce();
	reactionForceType ReactionForceType1();
	reactionForceType ReactionForceType2();
	void updatePosition(coordinateType ct, double dv);
	static unsigned int NDimension();
	static unsigned int NTotalNonZero();
	static void setIgnoreAllOptions(bool b);
	static void setSolverStep(unsigned int ss);
	bool IsFixedWhenKinematicAnalysis();

	virtual int constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul = 0) = 0;
	virtual void constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int i, bool isjp = false) = 0;
	virtual void derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i) = 0;
	virtual void lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1 = 0, double mul = 1) = 0;

protected:
	//static unsigned int nAdditional
	bool isFixedWhenKinematicAnalysis;
	static bool ignoreAllOptions;
	static unsigned int s_step;
	static unsigned int nDimension;
	static unsigned int nTotalNNZ;
	double *jrforce;
	unsigned int nnz;
	unsigned int nrow;
	unsigned int srow;
	jointType jtype;
	reactionForceType rft1;
	reactionForceType rft2;
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