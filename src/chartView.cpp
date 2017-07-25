#include "chartView.h"
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QImage>

chartView::chartView(Chart* c)
	: QChartView(c)
	, ax(NULL)
	, ay(NULL)
	, m_coordX(NULL)
	, m_coordY(NULL)
	, m_coordHoverX(NULL)
	, m_coordHoverY(NULL)
	, m_rectHovered(NULL)
	, m_lineItemX(NULL)
	, m_lineItemY(NULL)
	, m_checkItem(NULL)
	, mchs(NULL)
	, previous_checking_distance(0)
	, checked_point_number(-1)
	, onMousePress(false)
{
	ax = new axis(0, 1);
	ay = new axis(0, 1);
	chart()->setAxisX(ax);
	chart()->setAxisY(ay);

	m_coordX = new QGraphicsSimpleTextItem(chart());
	m_coordY = new QGraphicsSimpleTextItem(chart());
	QPen penBorder;
	penBorder.setColor(QColor(0, 0, 0));
	penBorder.setWidth(1);
	m_coordX->setPen(penBorder);
	m_coordY->setPen(penBorder);
	m_rectHovered = new QGraphicsRectItem(chart());
	m_rectHovered->setBrush(QBrush(Qt::yellow));
	m_coordHoverX = new QGraphicsSimpleTextItem(m_rectHovered);
	m_coordHoverY = new QGraphicsSimpleTextItem(m_rectHovered);
	penBorder.setColor(QColor(0, 0, 0));
	penBorder.setWidth(1);
	m_coordHoverX->setPen(penBorder);
	m_coordHoverY->setPen(penBorder);

	m_lineItemX = new QGraphicsLineItem(chart());
	m_lineItemY = new QGraphicsLineItem(chart());
	QPen penLine;
	penLine.setColor(QColor(0, 0, 0));
	penLine.setStyle(Qt::DotLine);
	m_lineItemX->setPen(penLine);
	m_lineItemY->setPen(penLine);

	QImage img;
	QPixmap buffer;
	img.load(":/Resources/check_icon.png");
	buffer = QPixmap::fromImage(img);
	buffer = buffer.scaled(20, 20);
	m_checkItem = new QGraphicsPixmapItem(buffer, chart());
	m_checkItem->setVisible(false);

	setMouseTracking(true);
	chart()->setAcceptHoverEvents(true);
	chart()->setZValue(50);
	m_coordHoverX->setZValue(20);
	setRenderHint(QPainter::Antialiasing);
	QLineSeries *series = new QLineSeries;
	QScatterSeries *p_series = new QScatterSeries;
	p_series->setMarkerSize(10);
	
	chart()->addSeries(series);
	chart()->addSeries(p_series);

	mchs = new MCHSpline;
}

chartView::~chartView()
{
	if (ax) delete ax; ax = NULL;
	if (ay) delete ay; ay = NULL;
	if (m_coordX) delete m_coordX; m_coordX = NULL;
	if (m_coordY) delete m_coordY; m_coordY = NULL;
	if (m_coordHoverX) delete m_coordHoverX; m_coordHoverX = NULL;
	if (m_coordHoverY) delete m_coordHoverY; m_coordHoverY = NULL;
	if (m_rectHovered) delete m_rectHovered; m_rectHovered = NULL;
	if (m_checkItem) delete m_checkItem; m_checkItem = NULL;
	if (m_lineItemX) delete m_lineItemX; m_lineItemX = NULL;
	if (m_lineItemY) delete m_lineItemY; m_lineItemY = NULL;
	if (mchs) delete mchs; mchs = NULL;
	chart()->removeAllSeries();
}

bool chartView::setChartData(QVector<double>* x, QVector<double>* y, int d)
{
	QLineSeries *series = new QLineSeries;
	int n = x->size();
	//QVector<double>::iterator ix = x->begin();
	//QVector<double>::iterator iy = y->begin();
	double x_max = FLT_MIN;
	double x_min = FLT_MAX;
	double y_max = FLT_MIN;
	double y_min = FLT_MAX;
	int i = 0;
	for (i = 0; i < n; i += d)
	{
		double _x = x->at(i);
		double _y = y->at(i);
		series->append(_x, _y);
		x_min = _x < x_min ? _x : x_min;
		x_max = _x > x_max ? _x : x_max;
		y_min = _y < y_min ? _y : y_min;
		y_max = _y > y_max ? _y : y_max;
	}
 	if (i >= n)
 		series->append(x->at(n - 1), y->at(n -1));
	if (chart())
	{
		//QColor c = series->color();
		//series->setColor(QColor(255, 0, 0));
		//c = series->color();
// 		chart()->addSeries(series);
// 		ax = new axis(x_min, x_max);
// 		ay = new axis(y_min, y_max);
// 		chart()->setAxisX(ax);
// 		chart()->setAxisY(ay);
		//chart()->set
		
	}
	else
		return false;
	return true;
}

void chartView::mouseReleaseEvent(QMouseEvent *event)
{
	if (onMousePress && checked_point_number >= 0)
	{
		QScatterSeries *p_series = dynamic_cast<QScatterSeries*>(chart()->series().at(1));
		QLineSeries *series = dynamic_cast<QLineSeries*>(chart()->series().at(0));
		QPointF new_p = chart()->mapToValue(movingPos);
		p_series->replace(checked_point_number, new_p);
		mchs->update_curve(checked_point_number, new_p, series);
		mchs->calculate_curve_auto(series, checked_point_number - 1, checked_point_number + 1);
	}
	onMousePress = false;
}

void chartView::mousePressEvent(QMouseEvent *event)
{
	onMousePress = true;
	if (checked_point_number >= 0)
		return;
	QPointF xy = event->pos();
	QPointF p = chart()->mapToValue(xy);
	QLineSeries *series = NULL;
	QScatterSeries *p_series = NULL;
	if (chart()->series().size() == 0)
	{
// 		series = new QLineSeries;
// 		p_series = new QScatterSeries;
// 		chart()->addSeries(series);
// 		chart()->addSeries(p_series);
// 		this->mousePressEvent(event);
	}
	else
	{
		series = dynamic_cast<QLineSeries*>(chart()->series().at(0));
		p_series = dynamic_cast<QScatterSeries*>(chart()->series().at(1));
		/*if (series->count() > 0){*/
		mchs->monotonic_cubic_Hermite_spline(p);
		mchs->setData2LineSeries(series);
		//}
		//series->append(p.x(), p.y());
		p_series->append(p.x(), p.y());
		qDebug() << p.x() << " " << p.y() << "\n";
		//series->setPointsVisible(true);
		//if (series->)
	}

	QChartView::mousePressEvent(event);
}

void chartView::mouseMoveEvent(QMouseEvent *event)
{
	
	QPointF xy = event->pos();
	QPointF p = chart()->mapToValue(event->pos());
	//QGraphicsSimpleTextItem *m_coordX = new QGraphicsSimpleTextItem(chart());
	//QGraphicsSimpleTextItem *m_coordY = new QGraphicsSimpleTextItem(chart());
	if (p.x() <= ax->max() && p.x() >= ax->min() && p.y() <= ay->max() && p.y() >= ay->min())
	{
		m_coordHoverX->setVisible(true);
		m_coordHoverY->setVisible(true);
		m_rectHovered->setVisible(true);
		m_lineItemX->setVisible(true);
		m_lineItemY->setVisible(true);

		qreal x = chart()->mapToPosition(p).x();
		qreal y = chart()->mapToPosition(p).y();
		
		m_rectHovered->setRect(x, y - 31, 40, 30);

		qreal rectX = m_rectHovered->rect().x();
		qreal rectY = m_rectHovered->rect().y();
		qreal rectW = m_rectHovered->rect().width();
		qreal rectH = m_rectHovered->rect().height();

		/* We're setting the labels and nicely adjusting to chart axis labels (adjusting so the dot lines are centered on the label) */
		m_coordHoverX->setPos(rectX + rectW / 4 - 3, rectY + 1);
		m_coordHoverY->setPos(rectX + rectW / 4 - 3, rectY + rectH / 2 + 1);

		QPointF xp = chart()->mapToPosition(QPointF(p.x(), 0));
		QPointF yp = chart()->mapToPosition(QPointF(0, p.y()));
		m_lineItemX->setLine(xp.x(), xy.y(), xy.x(), xp.y()/* - 27*/);
		m_lineItemY->setLine(xp.x(), xy.y(), yp.x(), xy.y());

		/* Setting value to displayed with four digit max, float, 1 decimal */
		m_coordHoverX->setText(QString("%1").arg(p.x(), 4, 'f', 2, '0'));
		m_coordHoverY->setText(QString("%1").arg(p.y(), 4, 'f', 2, '0'));
		if (onMousePress && checked_point_number >= 0)
		{
			movingPos.setX(x);
			movingPos.setY(y);
			return;
		}
		checkingNearPoint(x, y);
	}
	else
	{
		m_coordHoverX->setVisible(false);
		m_coordHoverY->setVisible(false);
		m_rectHovered->setVisible(false);
		m_lineItemX->setVisible(false);
		m_lineItemY->setVisible(false);
	}
}

int chartView::checkingNearPoint(double px, double py)
{
	int cnumber = 0;
	QScatterSeries* p_series = dynamic_cast<QScatterSeries*>(chart()->series().at(1));
	QVector<QPointF> points = p_series->pointsVector();
	qDebug() << "checked_point_number : " << checked_point_number;
	if (checked_point_number >= 0)
	{
		double dx = px - chart()->mapToPosition(points.at(checked_point_number)).x();
		double dy = py - chart()->mapToPosition(points.at(checked_point_number)).y();
		double dist = sqrt(dx * dx + dy * dy);
		if (dist < 5)
		{
			m_checkItem->setPos(px, py);
			m_checkItem->setVisible(true);
		}
		else
		{
			m_checkItem->setVisible(false);
			checked_point_number = -1;
		}
		return checked_point_number;
	}
	previous_checking_distance = 0;
	checked_point_number = -1;
	if (!points.size())
		return -1;
	foreach(QPointF p, points)
	{
		double dx = px - chart()->mapToPosition(p).x();
		double dy = py - chart()->mapToPosition(p).y();
		double dist = sqrt(dx*dx + dy*dy);
		if (dist < 5)
		{
// 			qDebug() << "distance : " << dist;
// 			qDebug() << "previous_checking_distance : " << previous_checking_distance;
// 			if (dist < previous_checking_distance)
// 				qDebug() << "checking near point : " << p.x() << ", " << p.y();
//			previous_checking_distance = dist;
			checked_point_number = cnumber;
			qDebug() << "1checked_point_number : " << checked_point_number;
			return checked_point_number;
		}
// 		else
// 		{
// 			qDebug() << "no Cheking";
// 			previous_checking_distance = 0;
// 		}
		cnumber++;
	}
	return 0;
}