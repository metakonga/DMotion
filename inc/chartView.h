#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QLineSeries>
#include <QScatterSeries>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include "MCHSpline.h"
#include "chart.h"
#include "axis.h"

class chartView : public QChartView
{
public:
	chartView(Chart* c = 0);
	~chartView();

	bool setChartData(QVector<double>* x, QVector<double>* y, int d = 1);

private:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	int checkingNearPoint(double px, double py);

private:
	bool onMousePress;
	QPointF movingPos;
	int checked_point_number;
	double previous_checking_distance;
	axis *ax;
	axis *ay;
	QGraphicsPixmapItem *m_checkItem;
	QGraphicsRectItem *m_rectHovered;
	QGraphicsLineItem *m_lineItemX;
	QGraphicsLineItem *m_lineItemY;
	QGraphicsSimpleTextItem *m_coordX;// = new QGraphicsSimpleTextItem(chart());
	QGraphicsSimpleTextItem *m_coordY;// = new QGraphicsSimpleTextItem(chart());
	QGraphicsSimpleTextItem *m_coordHoverX;
	QGraphicsSimpleTextItem *m_coordHoverY;

	MCHSpline *mchs;
};

#endif