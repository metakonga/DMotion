#ifndef DUALMOTION_H
#define DUALMOTION_H

#include <QString>
#include <mkl.h>

#include "model.h"

class DualMotion : public model
{
	

public:
	DualMotion();
	~DualMotion();

	virtual void init();
	virtual	unsigned int kinematicAnalysis();

private:
	QList<QString> bodyList;
	QList<QString> constList;

	double tNormValue;

	unsigned int s_c;
	unsigned int s_k;
	unsigned int s_d;

	MATD m_kj;				// Matrix for kinematic analysis 
	VECD v_kv;				// Vector for kinematic analysis
	MATD m_d;				// Matrix for dynamic analysis
	VECD v_d;				// Vector for dynamic analysis

	VECD q;
	VECD qd;
	VECD qdd;
};

#endif