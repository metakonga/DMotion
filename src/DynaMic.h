#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <QThread>
#include <QString>
#include <QMutex>
#include <mkl.h>

#include "model.h"

class plotWindow;

class DynaMic : public QThread
{
	Q_OBJECT
		
public:
	DynaMic(model* _md = NULL);
	~DynaMic();

	int init();
	void setSimulationCondition(double _dt, double _et);
	void setModel(model* _md);
	void oneStepAnalysis(double ct);
	void setPlotWindow(plotWindow* pw);

private:
	void run() Q_DECL_OVERRIDE;
	void predictionStep();
	unsigned int correctionStep();
	bool saveResultData(double ct);
	unsigned int kinematicAnalysis();
	void jointReactionForceFromEOM();

signals:
	void finishedThread();
	void sendProcess(char, QString m = "");
	void sendPlotData(double xv, double yv);

private:
	MKL_INT lapack_one;
	MKL_INT lapack_info;
	MKL_INT *ptDof;
	MKL_INT *permutation;

	gravity g;
	//QVector<transformationMatrix> TM;
	bool _isKinematicModel;
	unsigned int nStep;
	unsigned int nCoord;
	unsigned int mdim;
	unsigned int tIteration;
	unsigned int cStep;
	double tNormValue;
	double ct;
	double dt;
	double et;
	double alpha;
	double gamma;
	double beta;
	double divBeta;
	double dt2accp;
	double dt2accv;
	double dt2acc;
	QMutex m_mutex;
	MATD lhs;
	SMATD jacobi;
	VECD rhs;
	VECD pre;
	VECD q;
	VECD qd;
	VECD qdd;
	VECD ipp;
	VECD ipv;
	model *md;
	plotWindow *plot;
};

#endif