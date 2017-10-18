#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QMainWindow>
#include "chartView.h"
#include <QColumnView>

class model;
class QStandardItem;
class QStandardItemModel;
class Callout;

class plotDialog : public QMainWindow
{
	Q_OBJECT

public:
	plotDialog(QWidget* parent = NULL);
	~plotDialog();

	void setModel(model* _md);

	private slots:
	void clicked(QModelIndex);

private:
	void columnViewAdjustSameSize(int ncol);
	void setBodyRoot(QStandardItem *p);
	void setJointForceRoot(QStandardItem *p);
	void resizeEvent(QResizeEvent *event);

private:
	int wWidth;
	int wHeight;
	int xSize;
	int ySize;
	int openColumnCount;
	chartView *vcht;
	QColumnView *cview;
	QStandardItemModel *cmodel;
	model* md;
	Callout *m_tooltip;
	QList<Callout *> m_callouts;
};
#endif