#ifndef POINTFOLLOWER_H
#define POINTFOLLOWER_H

#include "constraint.h"
#include "MCHSpline.h"
#include <QFile>

class pointFollower : public constraint
{
public:
	pointFollower(QString _name);
	~pointFollower();

	void initialize(vecd3& hp0, vecd3& hp1);
	//void defineFollower(QString _path, vecd3 cp);
	void setBaseMarker(vecd3 q, vecd3 r);
	//void setDistance2Curve(VECD &q);
	void setLocalFromBaseBody();
//	void setDerivative2Curve(VECD &q);
	void setInitialAngle(double a);
	void setCurrentStep(unsigned int cid);
	void setActionHardPoint(vecd3 hp);
	void saveProfileData(QString _path);
	void appendProfileData(double th, double s);

	void defineOnePointFollower();
	void followerJacobian(VECD& q, SMATD& lhs, unsigned int r, unsigned int c);
	void initializeCurveData();
	void setCM2HardPoint();
	QVector<QPointF>& ProfileData();
	QVector<QPointF>& LastProfileData();
	void updateBaseMarker();
	vecd3 LocalFromBaseBody();
	void appendRealCamProfileXY(vecd3 xy);
	double MaxDistance();
	//double currentDthDt();
	void defineLast();

	virtual int constraintEquation(VECD &q, VECD &rhs, unsigned int i, double mul = 0);
	virtual void constraintJacobian(VECD &q, VECD &qd, SMATD &lhs, unsigned int i, bool isjp = false);
	virtual void derivative(VECD &q, VECD &qd, VECD &rhs, unsigned int i);
	virtual void lagrangianJacobian(VECD &q, MATD &lhs, unsigned int i, double lm0, double lm1 = 0, double mul = 1);

	double result_theta;
	double result_s;
	double result_dsdt;
	double result_dsdt2;

private:
	bool isSetVariableMarker;
	unsigned int current_step;
	double pre_theta;
	double base_angle; 
	double maxDistance;
	vecd3 for_s;
	vecd3 s;
	vecd3 rot_s;
	vecd3 local_vector;
	vecd3 action_hp;
	int incAngle;
	double sr;
// 	double ds;
// 	double dds;

//	QFile iqf;
	//MCHSpline* mch;
	unsigned int cur;
	QString profile_path;
	//QVector<double> deg;
	//QVector<vecd3> rdaa;
	QVector<QPointF> cpXY;
	QVector<QPointF> ss;
	QVector<double> ds;
	QVector<QPointF> endXY;
};

#endif