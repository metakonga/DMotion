#include "vp_profile.h"
#include <QLineSeries>
#include <QtWidgets>
#include <QtCharts>
//#include <QAbstractAxis>

vp_profile::vp_profile(QWidget* parent)
	: QDockWidget(parent)
	, vcht(NULL)
//	, cht(NULL)
// 	, mchs(NULL)
// 	, itor(NULL)
// 	, T(NULL)
// 	, V(NULL)
// 	, P(NULL)
{
	//mchs = new MCHSpline;
	//itor = new integrator;
// 	T = new QVector<double>;
// 	V = new QVector<double>;
// 	P = new QVector<double>;
// 	QVector<double> x_src(11);
// 	QVector<double> y_src(11);
 	Chart *cht = new Chart();
// 	x_src[0] = 0; x_src[1] = 0.1; x_src[2] = 0.2; x_src[3] = 0.3; x_src[4] = 0.4;
// 	x_src[5] = 0.5; x_src[6] = 0.6; x_src[7] = 0.7; x_src[8] = 0.8; x_src[9] = 0.9; x_src[10] = 1.0;
// 
// 	y_src[0] = 0; y_src[1] = -0.980665; y_src[2] = -1.96133; y_src[3] = -2.941995; y_src[4] = -3.92266;
// 	y_src[5] = -4.903325; y_src[6] = -5.88399; y_src[7] = -6.864655; y_src[8] = -7.84532; y_src[9] = -8.825985; y_src[10] = -9.80665;

	//mchs->monotonic_cubic_Hermite_spline(1.0, x_src, y_src);
	//mchs->calculate_curve(0.001, x_src, y_src, T, V);
	//mchs->calculate_curve(0.001, x_src, y_src, xPos, yPos);
	//itor->calculatePositionFromVelocity(0.3068, 0.0001, V, P);
	vcht = new chartView(cht);
	//vcht->setChartData(T, V, 10);
	vcht->chart()->legend()->hide();
  	vcht->chart()->setTitle("Simple line chart example");
	//dynamic_cast<QLineSeries*>(vcht->chart()->series().at(0))->setColor(QColor(255, 0, 0));
	vcht->resize(400, 300);
	setWidget(vcht);
}

vp_profile::~vp_profile()
{
//	if (vcht) delete vcht; vcht = NULL;
// 	if (mchs) delete mchs; mchs = NULL;
// 	if (itor) delete itor; itor = NULL;
// 	if (T) delete T; T = NULL;
// 	if (P) delete P; P = NULL;
// 	if (V) delete V; V = NULL;
}