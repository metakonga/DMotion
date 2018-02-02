#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDockWidget>
#include <QComboBox>
#include <QMap>
#include "dmotion_types.h"
#include "chartView.h"

class model;
class optimumDesignDoc;

class plotWindow : public QDockWidget
{
	Q_OBJECT 

public:
	plotWindow(model* _md, QWidget* parent);
	~plotWindow();

	QLineSeries* createSeries(QString n);
	void appendData(QString n, double x, double y, bool urange);
	void showSeries(QString str);
	void hideSeries(QString str = "");
	void setXRange(QString str, double ma, double mi);
	void setYRange(QString str, double ma, double mi);
	void setAxisTitle(QString str, QString xt, QString yt);
	void setPlotComboBox();
	void bindOptimumDesignDoc(optimumDesignDoc* _odd);
	void updatePlotData();
	void updateByModelChange();
	void adjustAxisRange(QString str);

	private slots:
	void changeCoordinateComboBox(int);
	void changeObjectComboBox(int);

private:
	QComboBox* cb_plot_object;
	QComboBox* cb_plot_coord;

	bool inObjectComboBox;
	int currentDataType;
	QString currentSeries;
	double m_min_x;
	double m_max_x;
	double m_min_y;
	double m_max_y;
	chartView *vcht;
	QMap<QString, QLineSeries*> seriesMap;
	QMap<QString, plotInfo> pInfo;
	//QMap<QString, QPointF> y_range;

	model *md;
	optimumDesignDoc *odd;
};

#endif