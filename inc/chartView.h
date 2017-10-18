#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QLineSeries>
#include <QScatterSeries>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QTableWidget>
#include "MCHSpline.h"
//#include "chart.h"
#include "axis.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

class Callout;

QT_CHARTS_USE_NAMESPACE

class chartView : public QGraphicsView
{
	Q_OBJECT

public:
	chartView(QWidget* parent = 0);
	~chartView();

	enum ChartMode{ REALTIME_EDIT_CHART = 0, ONLY_DISPLAY_CHART };
	void addSeries(QLineSeries *_series);
	void setAxisRange(double x_min, double x_max, double y_min, double y_max);
	bool setChartData(QVector<double>* x, QVector<double>* y, int d = 1);
	void setTableWidget(QTableWidget* _table) { table = _table; }
	void setChartMode(ChartMode _cmode);

private:
	//void mousePressEvent(QMouseEvent *event);
	//void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent *event);

	int checkingNearPoint(double px, double py);
	void updateSeries(double newXmax, double newTmax);

	public slots:
	void keepCallout();
	void tooltip(QPointF, bool);


private:
	ChartMode cmode;
	bool onMousePress;
	bool onMouseMiddleButton;
	QPointF movingPos;
	QPointF nonMovingPos;
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

	QGraphicsScene *m_scene;
	QChart *m_chart;
	MCHSpline *mchs;
	QTableWidget *table;
	Callout *m_tooltip;
	QList<Callout *> m_callouts;

};

#endif