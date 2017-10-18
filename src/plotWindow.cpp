#include "plotWindow.h"

plotWindow::plotWindow(QWidget* parent)
	: QDockWidget(parent)
	, vcht(NULL)
	, m_min_y(DBL_MAX)
	, m_max_y(-DBL_MAX)
	, m_min_x(DBL_MAX)
	, m_max_x(-DBL_MAX)
{
	vcht = new chartView(this);
	setWidget(vcht);
}

plotWindow::~plotWindow()
{
	qDeleteAll(seriesMap);
}

void plotWindow::createSeries(QString n)
{
	QLineSeries* lineSeries = new QLineSeries;
	lineSeries->setName(n);
	vcht->addSeries(lineSeries);
	seriesMap[n] = lineSeries;
}

void plotWindow::appendData(QString n, double x, double y)
{
	m_min_x = (m_min_x > x) ? x : m_min_x;
	m_max_x = (m_max_x < x) ? x : m_max_x;
	m_min_y = (m_min_y > y) ? y : m_min_y;
	m_max_y = (m_max_y < y) ? y : m_max_y;
	seriesMap[n]->append(x, y);
	vcht->setAxisRange(m_min_x, m_max_x, m_min_y, m_max_y);
}
