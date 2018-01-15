#ifndef DRIVING_CONDITION_PLOT_H
#define DRIVING_CONDITION_PLOT_H

#include <QWidget>
#include "chartView.h"
#include <QVector>

QT_BEGIN_NAMESPACE
class QPointF;
class QFrame;
QT_END_NAMESPACE

class drivingConditionPlot : public QWidget
{
	enum {NOZZLE_CHART = 0, ARC_CHART};
public:
	drivingConditionPlot(QWidget* parent, QFrame *FNozzle, QFrame *FArc);
	~drivingConditionPlot();

	void setNozzlePlot(QVector<QPointF>& data);
	void setArcPlot(QVector<QPointF>& data);

private:
	chartView *nozzleChart;
	chartView *arcChart;
};

#endif