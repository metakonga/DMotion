#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <QThread>
#include <QString>
#include <QMutex>
//#include <mkl.h>

#include "model.h"



class plotWindow;
class optimumDesignDoc;

class kinematics : public QThread
{
	Q_OBJECT
		
public:
	kinematics(model* _md = NULL, optimumDesignDoc* _odd = NULL);
	~kinematics();

	int init();
	void setSimulationCondition(double _dt, double _et);
	void setModel(model* _md);
	//void oneStepAnalysis(double ct);
	void setPlotWindow(plotWindow* pw);
	//void saveResultDataToTXTFile(QString path);
	void saveBodyResults();
	void setDesignVariables(MATD& m_design);

private:
	void run() Q_DECL_OVERRIDE;
//	void predictionStep();
	//unsigned int correctionStep();
	//bool saveResultData(double ct);
	int kinematicAnalysis(/*QVector<double> &pacc*/);
	void jointReactionForce(unsigned int r_step);
	//void jointReactionForceFromEOM();
	//void saveReactionForceData();
	void initGeneralizedCoordinates();

signals:
	void finishedThread();
	void sendProcess(char, QString m = "");
	void sendCaseCount(int count);

private:
	gravity g;
	unsigned int s_c;
	unsigned int s_k;
	unsigned int s_d;

	unsigned int m_id;
	unsigned int reaction_step;
	unsigned int nStep;
	unsigned int mdim;
	int tIteration;
	unsigned int cStep;
	double tNormValue;
	double ct;
	double dt;
	double et;
	QMutex m_mutex;
	VECD q;
	VECD qd;
	VECD qdd;
	MATD design;
	model *md;
	plotWindow *plot;
	QFile odbg;
	
	optimumDesignDoc* odd;
	QVector<vecd3> cam_profile;
};

#endif