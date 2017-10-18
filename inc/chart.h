#ifndef CHART_H
#define CHART_H

#include <QChart>
#include <QVector>

class QGestureEvent;

QT_CHARTS_USE_NAMESPACE

class Chart : public QChart
{
	//Q_OBJECT
public:
	explicit Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
	~Chart();

	QVector<double>& xSource() { return x_src; }
	QVector<double>& ySource() { return y_src; }

private:
	QVector<double> x_src;
	QVector<double> y_src;
	QVector<double> x_data;
	QVector<double> y_data;
};

#endif