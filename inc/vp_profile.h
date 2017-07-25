#ifndef VP_PROFILE_H
#define VP_PROFILE_H

#include <QDockWidget>
#include "MCHSpline.h"
#include "chartView.h"
#include "integrator.h"

class vp_profile: public QDockWidget
{
public:
	vp_profile(QWidget* parent = 0);
	~vp_profile();

private:
//	Chart *cht;
// 	QVector<double> *T;
// 	QVector<double> *V;
// 	QVector<double> *P;
// 	//QVector<double> *yPos;
	chartView *vcht;
// 	MCHSpline *mchs;
// 	integrator *itor;
};

#endif