#ifndef MODEL_H
#define MODEL_H

//#include <QMap>
#include <QVector>
#include <QString>
#include <gp_Pnt.hxx>
#include "rigidBody.h"
#include "revoluteJoint.h"
#include "translateJoint.h"
#include "drivingConstraint.h"

//class QStandardItem;

class model
{
public:
	model();
	~model();

	void setModelName(QString _modelName);
	QString ModelName();
	QVector<resultDataType>* bodyResultData(QString _name);
	QVector<jointResultDataType>* jointResultData(QString _name);

	hardPoint* createHardPoint(QString _name, double x, double y, double z);
	vecd3 getHalfBetween2HP(hardPoint* hpi, hardPoint* hpj);
	vecd3 getDiffBetween2HP(hardPoint* hpi, hardPoint* hpj);
	double getAngleBetween2HP(hardPoint* hpi, hardPoint* hpj);
	double getLengthBetween2HP(hardPoint* hpi, hardPoint* hpj);
	//hardPoint* getHardPoint(QString hp);
	unsigned int nBody();
	int hasGround();
	rigidBody* createRigidBody(QString _name);
	revoluteJoint* createRevoluteJoint(QString _name);
	translateJoint* createTraslateJoint(QString _name);
	drivingConstraint* createDrivingConstraint(QString _name);

	QVector<rigidBody*>& RigidBodies();
	QVector<constraint*>& Constraints();
	QVector<hardPoint*>& HardPoints();
	QVector<drivingConstraint*>& DrivingConstraints();

	virtual void init() = 0;

private:
	QString modelName;
	int _isHasGroundModel;
	QVector<hardPoint*> hardPoints;
	QVector<rigidBody*> bodies;
	QVector<constraint*> cons;
	QVector<drivingConstraint*> drivings;
// 	QList<QStandardItem*> bodyResultItems;
// 	QList<QStandardItem*> forceResultItems;
// 	QList<QStandardItem*> jointResultItems;

};
#endif