#include "dmotion.h"
#include "vp_profile.h"
//#include "MCHSpline.h"
// #include <QChartView>
// #include <QLineSeries>
//#include <QDialog>

DMotion::DMotion(QWidget *parent)
	: QMainWindow(parent)
	, vp(NULL)
{
	ui.setupUi(this);
	vp = new vp_profile(this);
	//vp_profile *vp2 = new vp_profile(this);
	addDockWidget(Qt::RightDockWidgetArea, vp);
//	addDockWidget(Qt::RightDockWidgetArea, vp2);
// 	QLineSeries *series = new QLineSeries();
// // 	series->append(0, 6);
// // 	series->append(2, 4);
// // 	series->append(3, 8);
// // 	series->append(7, 4);
// // 	series->append(10, 5);
// // 	*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
// 	QVector<double> x_src(10);
// 	QVector<double> y_src(10);
// 
// 	x_src[0] = 0; x_src[1] = 2; x_src[2] = 3; x_src[3] = 7; x_src[4] = 10;
// 	x_src[5] = 11; x_src[6] = 13; x_src[7] = 17; x_src[8] = 18; x_src[9] = 20;
// 
// 	y_src[0] = 6; y_src[1] = 4; y_src[2] = 8; y_src[3] = 4; y_src[4] = 5;
// 	y_src[5] = 1; y_src[6] = 3; y_src[7] = 6; y_src[8] = 3; y_src[9] = 2;
// 
// 	MCHSpline mchs;
// 	mchs.monotonic_cubic_Hermite_spline(20, x_src, y_src);
// 
// 	mchs.setData2LineSeries(series);
// 
// 	QChart *chart = new QChart();
// 	chart->legend()->hide();
// 	chart->addSeries(series);
// 	chart->createDefaultAxes();
// 	chart->setTitle("Simple line chart example");
// 
// 	QChartView *chartView = new QChartView(chart);
// 	chartView->setRenderHint(QPainter::Antialiasing);
// 
// 	chartView->show();
// // 	this->setCentralWidget(chartView);
// // 	this->resize(400, 300);

}

DMotion::~DMotion()
{
	if (vp) delete vp; vp = NULL;
}
