#ifndef DMOTION_H
#define DMOTION_H

#include <QtWidgets/QMainWindow>
#include "ui_dmotion.h"

class vp_profile;

class DMotion : public QMainWindow
{
	Q_OBJECT

public:
	DMotion(QWidget *parent = 0);
	~DMotion();

private:
	Ui::DMotionClass ui;
	vp_profile *vp;
};

#endif // DMOTION_H
