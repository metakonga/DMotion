#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDockWidget>
#include <QMap>
#include "chartView.h"

class plotWindow : public QDockWidget
{
public:
	plotWindow(QWidget* parent);
	~plotWindow();

	void createSeries(QString n);
	void appendData(QString n, double x, double y);

private:
	double m_min_x;
	double m_max_x;
	double m_min_y;
	double m_max_y;
	chartView *vcht;
	QMap<QString, QLineSeries*> seriesMap;
};

#endif