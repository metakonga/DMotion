#ifndef VP_PROFILE_H
#define VP_PROFILE_H

#include <QDialog>
#include "ui_velocityProfile.h"
#include "MCHSpline.h"
#include "chartView.h"
#include "integrator.h"
#include "drivingConstraint.h"

class vp_profile : public QDialog, private Ui::VP_Dialog
{
	Q_OBJECT
	enum SeriesType{ NOZZLE_VELOCITY = 0, ARC_STROKE, ARC_VELOCITY, ARC_ACCELERATION, RELATIVE_VELOCITY, VELOCITY_RATIO, INTERPOLATION_POINT };
public:
	vp_profile(QString _path, QWidget* parent = 0);
	~vp_profile();

	void setActiveProfile(QVector<double>& vp);
	void changeTableData(int row, QPointF new_v);

	private slots:
	void finishDialog(int);
	void clickRadioButton_Velocity();
	void clickRadioButton_Acceleration();
	void clickRadioButton_Stroke();
	void clickRadioButton_RelativeVelocity();
	void clickRadioButton_VelocityRatio();
	void changeCellItem(QTableWidgetItem*);
	void doubleClicked(QTableWidgetItem*);
	void exportData();
	void importData();
	void changeSeries(int idx);
	

private:
	bool _isClicedCell;
	bool _isChangeData;
	QString userPath;
	QVector<QPointF> rdata;
	QMap<int, QList<QPointF>> dataMap;
	int xSize;
	int ySize;
	chartView *vcht0;
	chartView *vcht1;
	drivingConstraint *drive;
	//QVector<QObject*> objs;
};

#endif