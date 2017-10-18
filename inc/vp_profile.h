#ifndef VP_PROFILE_H
#define VP_PROFILE_H

#include <QDialog>
#include "MCHSpline.h"
#include "chartView.h"
#include "integrator.h"

class vp_profile : public QDialog
{
	Q_OBJECT

public:
	vp_profile(QWidget* parent = 0);
	~vp_profile();

	private slots:
	void finishDialog(int);

private:
	int xSize;
	int ySize;
	chartView *vcht;
	QTableWidget *table;
};

#endif