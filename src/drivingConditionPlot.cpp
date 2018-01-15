#include "drivingConditionPlot.h"
#include <QVector>
#include <QPointF>
#include <QFrame>
#include <QBoxLayout>

drivingConditionPlot::drivingConditionPlot(QWidget* parent, QFrame *FNozzle, QFrame *FArc)
	: QWidget(parent)
	, nozzleChart(NULL)
	, arcChart(NULL)
{
// 	QWidget *layoutNozzle = new QWidget(FNozzle);
// 	layoutNozzle->setObjectName(QStringLiteral("LayoutNozzle"));
	//QBoxLayout *layoutNozzle = new QBoxLayout(QBoxLayout::Direction::Down, FNozzle);
// 	FNozzle->setLineWidth(0);
// 	FArc->setLineWidth(0);
	nozzleChart = new chartView(FNozzle);
	nozzleChart->Chart()->setMaximumSize(120, 50);
	nozzleChart->Chart()->setMinimumSize(120, 50);
	//nozzleChart->setAxisRange(0, 0.035, -9.0, 0.1);
	nozzleChart->Chart()->axisX()->hide();
	nozzleChart->Chart()->axisY()->hide();
	nozzleChart->Chart()->legend()->setVisible(false);
	nozzleChart->Chart()->setMargins(QMargins(0, 0, 0, 0));
//	FNozzle->set

	arcChart = new chartView(FArc);
	arcChart->Chart()->setMaximumSize(120, 50);
	arcChart->Chart()->setMinimumSize(120, 50);
	//arcChart->setAxisRange(0, 0.035, -9.0, 0.1);
	arcChart->Chart()->axisX()->hide();
	arcChart->Chart()->axisY()->hide();
	arcChart->Chart()->legend()->setVisible(false);
	arcChart->Chart()->setMargins(QMargins(0, 0, 0, 0));

	nozzleChart->createLineSeries(NOZZLE_CHART);
	arcChart->createLineSeries(ARC_CHART);
}

drivingConditionPlot::~drivingConditionPlot()
{
	if (nozzleChart) delete nozzleChart; nozzleChart = NULL;
	if (arcChart) delete arcChart; arcChart = NULL;
}

void drivingConditionPlot::setNozzlePlot(QVector<QPointF>& data)
{
	QLineSeries* nozzleSeries = nozzleChart->LineSeries()[NOZZLE_CHART];
	if (nozzleSeries->count())
		nozzleSeries->clear();
	int i = 0;
	double y_max = -FLT_MAX;
	double y_min = FLT_MAX;
	foreach(QPointF p, data)
	{
		if (p.y() > y_max)
			y_max = p.y();
		if (p.y() < y_min)
			y_min = p.y();
		nozzleSeries->append(p.x(), p.y());
	}
	nozzleChart->setAxisRange(0, 0.035, y_min, y_max);
}

void drivingConditionPlot::setArcPlot(QVector<QPointF>& data)
{
	QLineSeries* arcSeries = arcChart->LineSeries()[ARC_CHART];
	if (arcSeries->count())
		arcSeries->clear();
	int i = 0;
	double y_max = -FLT_MAX;
	double y_min = FLT_MAX;
	foreach(QPointF p, data)
	{
		if (p.y() > y_max)
			y_max = p.y();
		if (p.y() < y_min)
			y_min = p.y();
		arcSeries->append(p.x(), p.y());
	}
	arcChart->setAxisRange(0, 0.035, y_min, y_max);
}
