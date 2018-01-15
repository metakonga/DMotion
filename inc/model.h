#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QString>
#include <gp_Pnt.hxx>
#include "rigidBody.h"
#include "pointFollower.h"
#include "revoluteJoint.h"
#include "translateJoint.h"
#include "verticalConstraint.h"
#include "drivingConstraint.h"
#include "constantConstraint.h"
#include "designVariable.h"

//class QStandardItem;

class model
{
public:
	model(modelType mt = ORIGINAL_CAM_TYPE);
	~model();

	void setModelName(QString _modelName);
	void setModelPath(QString _modelPath);
	QString ModelName();
	QString ModelPath();
	QVector<resultDataType>* bodyResultData(QString _name);
	QVector<jointResultDataType>* jointResultData(QString _name);

	void setCoordinateNumber(unsigned int nc);
	void setCamAngleDesignVariable(double lo, double up);
	void setCamAngleDesignVariableEnable(bool b);
	void setLastCamAngleDesignVariable(double lo, double up);
	void setLastCamAngleDesignVariableEnable(bool b);
	void setSpaceConstraint(double sw, double sh);
	void setGeneralizedCoordinate(unsigned int step, VECD& q, VECD& qd, VECD& qdd);
	bool updateDesignVariable(QString &hps, bool isFirst = false);
	bool IsEmptyEnableDesignVariable();
	bool IsSatisfyCamAngle();
	void initializeDesignVariable();
	double NoSatisfiedCamAngle();

	//reactionForceType Constraint2ReactionType(QString _name, coordinateType ctype);

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
	pointFollower* createPointFollower(QString _name);
	verticalConstraint* createVerticalConstraint(QString _name);
	constantConstraint* createConstantConstraint(QString _name);
	designVariable* createDesignVariable(QString _name);

	pointFollower* PointFollower();

	QList<QString>& HardPointList();
	QList<QString>& BodyList();
	QList<QString>& ConstraintList();
	QMap<QString, rigidBody*>& RigidBodies();
	QMap<QString, constraint*>& Constraints();
	QMap<QString, hardPoint*>& HardPoints();
	QMap<QString, drivingConstraint*>& DrivingConstraints();
	QMap<QString, designVariable*>& DesignVariables();
	QMap<int, reactionForceType>& ReactionMap();
	//QMap<QString, pointFollower*>& PointFollowers();

	modelType ModelType();
	double SpaceConstraintWidth();
	double SpaceConstraintHeight();
	bool verifyLastCamAngleConstraint(QMap<QString, QVector<vecd3>>& hps);

	virtual void init() = 0;
//	virtual unsigned int kinematicAnalysis() = 0;

protected:
	modelType mtype;
	bool isEmptyEnableDesignVariable;
	bool isSatisfyCamAngle;
	//bool isSatisfyLastCamAngle;
	unsigned int nCoordinates;
	QString modelName;
	QString modelPath;
	int _isHasGroundModel;
	bool cam_angle_enable;
	bool last_cam_angle_enable;
	double cam_angle_lower;
	double cam_angle_upper;
	double last_cam_angle_lower;
	double last_cam_angle_upper;
	double noSatisfiedCamAngle;
	double spaceWidth;
	double spaceHeight;

	QList<QString> hpList;
	QList<QString> bodyList;
	QList<QString> constList;
	QMap<QString, hardPoint*> hardPoints;
	QMap<QString, rigidBody*> bodies;
	QMap<QString, constraint*> cons;
	QMap<QString, designVariable*> designs;
	pointFollower* pfollower;
	QMap<QString, drivingConstraint*> drivings;
	QMap<int, reactionForceType> reactionMap;
};
#endif