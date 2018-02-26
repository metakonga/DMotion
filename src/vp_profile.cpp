#include "vp_profile.h"
#include <QLineSeries>
#include <QtWidgets>
#include <QtCharts>
#include "dmotion_types.h"
#include "messageBox.h"
//#include <QAbstractAxis>

vp_profile::vp_profile(QString _path, QWidget* parent)
	: QDialog(parent)
	, vcht0(NULL)
	, vcht1(NULL)
	, xSize(640)
	, ySize(480)
	, _isClicedCell(false)
	, _isChangeData(false)
	, userPath(_path)
{
	setupUi(this);
 	//Chart *cht = new Chart();
	vcht0 = new chartView(this, chartView::REALTIME_EDIT_CHART);
	vcht1 = new chartView(this);
	TB_Table->setColumnCount(3);
	//table = new QTableWidget(0, 3);
	TB_Table->setSelectionBehavior(QAbstractItemView::SelectRows);
	QStringList labels;
	labels << "ID" << "X Data" << "Y Data";
	TB_Table->setHorizontalHeaderLabels(labels);
	TB_Table->verticalHeader()->hide();
	TB_Table->setShowGrid(true);
	TB_Table->horizontalHeader()->setDefaultSectionSize(70);
	//TB_Table->setMinimumWidth(210);
	//TB_Table->setMaximumWidth(210);
	vcht0->setTableWidget(TB_Table);
// 	QGroupBox *GB_INFO = new QGroupBox("Information"); objs.push_back(GB_INFO);
// 	QLabel* L_Stroke = new QLabel("Stroke");
// 	QLabel* L_Ratio = new QLabel("Min. ratio");
// 	QLabel* L_MaxRV = new QLabel("Max. RVel");
// 
// 	resize(xSize, ySize);
	connect(this, SIGNAL(finished(int)), this, SLOT(finishDialog(int)));
// 	QGroupBox *GB_RADIO = new QGroupBox("Series"); objs.push_back(GB_RADIO);
// 	QRadioButton *RB_VELOCITY = new QRadioButton("Velocity", GB_RADIO);
// 	RB_VELOCITY->setChecked(true);
// 	QRadioButton *RB_STROKE = new QRadioButton("Stroke", GB_RADIO);
// 	QRadioButton *RB_ACCELERATION = new QRadioButton("Acceleration", GB_RADIO);
// 	QHBoxLayout *rb_layout = new QHBoxLayout;// objs.push_back(rb_layout);
// 	rb_layout->addWidget(RB_VELOCITY);
// 	rb_layout->addWidget(RB_STROKE);
// 	rb_layout->addWidget(RB_ACCELERATION);
// 	GB_RADIO->setLayout(rb_layout);
// 	QPushButton* PBEX = new QPushButton("Export"); objs.push_back(PBEX);
// 	QGroupBox *GB_OPTION = new QGroupBox("Options"); objs.push_back(GB_OPTION);
// 	QCheckBox *CB_Manual = new QCheckBox("Manual"); 
// 	QCheckBox *CB_Auto = new QCheckBox("Auto");
// 	QHBoxLayout *cb_layout = new QHBoxLayout;
// 	cb_layout->addWidget(CB_Manual);
// 	cb_layout->addWidget(CB_Auto);
// 	QLabel* L_Stroke = new QLabel("Stroke");
// 	QLabel* L_MaximumRV = new QLabel("Relative Vel.");
// 	QVBoxLayout *a_layout = new QVBoxLayout; objs.push_back(a_layout);
//  	a_layout->addWidget(GB_RADIO);
// 	a_layout->addWidget(PBEX);
// 	QVBoxLayout *ac_layout = new QVBoxLayout; objs.push_back(ac_layout);
// 	ac_layout->addWidget(vcht);
// 	ac_layout->addLayout(a_layout);
// 	QHBoxLayout *h_layout = new QHBoxLayout;// objs.push_back(ay_layout);
// 	//h_layout->addWidget(vcht);
// 	h_layout->addLayout(ac_layout);
// 	h_layout->addWidget(table);
	SA_Profile->setWidget(vcht0);
	SA_Result->setWidget(vcht1);
	//setLayout(h_layout);
// /	connect(LEAXIS_X_LIMIT, SIGNAL(editingFinished()), this, SLOT(changeAxisXLimit()));
// 	connect(LEAXIS_Y_LIMIT, SIGNAL(editingFinished()), this, SLOT(changeAxisYLimit()));
	

	vcht0->setAxisRange(0, 0.035, -10.0, 14.0);
	vcht0->setTickCountY(13);
	vcht0->setTickCountX(8);
	vcht1->setTickCountX(8);
	//vcht0->setAxisXY();
	
	QScatterSeries* ip = vcht0->createScatterSeries(INTERPOLATION_POINT);
	CB_SeriesList->addItem("Interpolation point");
	QLineSeries* nozzle_vel = vcht0->createLineSeries(NOZZLE_VELOCITY);
	CB_SeriesList->addItem("Nozzle velocity");
	QLineSeries* stroke = vcht0->createLineSeries(ARC_STROKE);
	CB_SeriesList->addItem("Arc stroke");
	QLineSeries* vel = vcht0->createLineSeries(ARC_VELOCITY);
	CB_SeriesList->addItem("Arc velocity");
	QLineSeries* acc = vcht0->createLineSeries(ARC_ACCELERATION);
	CB_SeriesList->addItem("Arc acceleration");
	QLineSeries* rv = vcht1->createLineSeries(RELATIVE_VELOCITY);
	CB_SeriesList->addItem("Relative velocity");
	QLineSeries* vr = vcht1->createLineSeries(VELOCITY_RATIO);
	CB_SeriesList->addItem("Velocity ratio");
	
	ip->setMarkerSize(10);
	
	vcht0->setControlLineSeries(ARC_VELOCITY);
	vcht0->setControlScatterSeries(INTERPOLATION_POINT);
	
	stroke->hide();
	nozzle_vel->show();
	acc->hide();
	rv->hide();
	vr->hide();
	//CB_SeriesList->setModelColumn(INTERPOLATION_POINT);

	connect(RB_Velocity, SIGNAL(clicked()), this, SLOT(clickRadioButton_Velocity()));
	connect(RB_Stroke, SIGNAL(clicked()), this, SLOT(clickRadioButton_Stroke()));
	connect(RB_Acceleration, SIGNAL(clicked()), this, SLOT(clickRadioButton_Acceleration()));
	connect(RB_RelativeVelocity, SIGNAL(clicked()), this, SLOT(clickRadioButton_RelativeVelocity()));
	connect(RB_VelocityRatio, SIGNAL(clicked()), this, SLOT(clickRadioButton_VelocityRatio()));
	connect(TB_Table, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(changeCellItem(QTableWidgetItem*)));
	connect(TB_Table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(doubleClicked(QTableWidgetItem*)));
	connect(PB_Export, SIGNAL(clicked()), this, SLOT(exportData()));
	connect(PB_Import, SIGNAL(clicked()), this, SLOT(importData()));
	connect(CB_SeriesList, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSeries(int)));
}

vp_profile::~vp_profile()
{
	if (vcht0) delete vcht0; vcht0 = NULL;
	if (vcht1) delete vcht1; vcht1 = NULL;
}

void vp_profile::setActiveProfile(QVector<double>& vp)
{
	QLineSeries* ls = vcht0->LineSeries()[NOZZLE_VELOCITY];
	double t = 0;
	foreach(double d, vp)
	{
		ls->append(t, d);
		dataMap[NOZZLE_VELOCITY].push_back(QPointF(t, d));
		t += 0.00001;
	}
	//CB_SeriesList->addItem("Nozzle velocity");
}


void vp_profile::finishDialog(int result)
{
	xSize = width();
	ySize = height();
}

void vp_profile::clickRadioButton_Velocity()
{
	vcht0->LineSeries()[ARC_VELOCITY]->show();
	vcht0->ScatterSeries()[INTERPOLATION_POINT]->show();
// 	vcht0->Chart()->series().at(0)->show();
// 	vcht0->Chart()->series().at(1)->show();
	vcht0->LineSeries()[NOZZLE_VELOCITY]->show();
	vcht0->LineSeries()[ARC_STROKE]->hide();
	vcht0->LineSeries()[ARC_ACCELERATION]->hide();
	vcht0->setAxisRange(0, 0.035, -11.0, 14.0);
	vcht0->setEnableClickEvent(true);
}

void vp_profile::clickRadioButton_Acceleration()
{
	QLineSeries* series = vcht0->LineSeries()[ARC_VELOCITY];
	QScatterSeries* pseries = vcht0->ScatterSeries()[INTERPOLATION_POINT];
	if (pseries->count() < 3)
		return;
	QLineSeries* acc = vcht0->LineSeries()[ARC_ACCELERATION];
	//QList<QPointF> data;
	dataMap[ARC_ACCELERATION].clear();
	QVector<QPointF> vp = series->pointsVector();
	dataMap[ARC_ACCELERATION].push_back(QPointF(0, 0));
	acc->clear();
	acc->append(0, 0);
	double max_p = DBL_MIN;
	double min_p = DBL_MAX;
	for (unsigned int i = 1; i < vp.size() - 1; i++)
	{
		double dt = vp.at(i + 1).x() - vp.at(i - 1).x();
		double dv = vp.at(i + 1).y() - vp.at(i - 1).y();
		double a = dv / dt;
		double t = vp.at(i).x();
		dataMap[ARC_ACCELERATION].push_back(QPointF(t, a));
		if (!(i % 10))
			acc->append(t, a);
		if (max_p < a)
			max_p = a;
		if (min_p > a)
			min_p = a;
	}
	//double x = vp.at(vp.size() - 1).x();
	dataMap[ARC_ACCELERATION].push_back(QPointF(0.035, 0.0));
	//acc->clear();
	//acc->append(data);
	series->hide();
	vcht0->LineSeries()[NOZZLE_VELOCITY]->hide();
	vcht0->LineSeries()[ARC_STROKE]->hide();
	vcht0->ScatterSeries()[INTERPOLATION_POINT]->hide();
	vcht0->setAxisRange(0, 0.035, min_p, max_p);
	acc->show();
	vcht0->setEnableClickEvent(false);
}

void vp_profile::clickRadioButton_Stroke()
{
	integrator itor;
	QLineSeries* series = vcht0->LineSeries()[ARC_VELOCITY];
	QLineSeries* stroke = vcht0->LineSeries()[ARC_STROKE];
	//QList<QPointF> data;
	dataMap[ARC_STROKE].clear();
	itor.calculatePositionFromVelocity(0.0, 0.00001, series->pointsVector(), dataMap[ARC_STROKE]);
	stroke->clear();
	int sz = dataMap[ARC_STROKE].size();
	QPointF p;
	double minv = DBL_MAX;
	double maxv = DBL_MIN;
	for (int i = 0; i < sz; i++)
	{
		if (!(i % 10))
		{
			p = dataMap[ARC_STROKE].at(i);
			stroke->append(p.x(), p.y());
		}
		if (p.y() > maxv)
			maxv = p.y();
		if (p.y() < minv)
			minv = p.y();			
	}
	p = dataMap[ARC_STROKE].at(sz - 1);
	stroke->append(p.x(), p.y());
	//stroke->append(data);
	series->hide();
	vcht0->Chart()->series().at(1)->hide();
	vcht0->LineSeries()[NOZZLE_VELOCITY]->hide();
	vcht0->LineSeries()[ARC_ACCELERATION]->hide();
	vcht0->ScatterSeries()[INTERPOLATION_POINT]->hide();
	double d = (maxv - minv) * 0.01;
	vcht0->setAxisRange(0, 0.035, minv - d, maxv + d);
	stroke->show();
	vcht0->setEnableClickEvent(false);
}

void vp_profile::changeTableData(int row, QPointF new_v)
{
	QTableWidgetItem* item = TB_Table->item(row, 1);
	item->setText(QString("%1").arg(new_v.x()));
	_isClicedCell = true;
	changeCellItem(item);
	item = TB_Table->item(row, 2);
	item->setText(QString("%1").arg(new_v.y()));
	_isClicedCell = true;
	changeCellItem(item);
}

bool vp_profile::checkFirstEndData()
{
	QTableWidgetItem* f_item0 = TB_Table->item(0, 1);
	QTableWidgetItem* f_item1 = TB_Table->item(0, 2);
	int nrow = TB_Table->rowCount() - 1;
	QTableWidgetItem* e_item0 = TB_Table->item(nrow, 1);
	QTableWidgetItem* e_item1 = TB_Table->item(nrow, 2);
	if (f_item0->text().toDouble() != 0) return false;
	if (f_item1->text().toDouble() != 0) return false;
	if (e_item0->text().toDouble() != 0.035) return false;
	if (e_item1->text().toDouble() != 0) return false;
	return true;
}

void vp_profile::clickRadioButton_RelativeVelocity()
{
	bool chk = checkFirstEndData();
	if (!chk)
	{
		int ret = messageBox::run("The velocity profile of arc is incorrect.\nYou must determine the start and end points.", "Do you want to continue the process.\nProfile data will be changed to start(0, 0) and end(0.035, 0).", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		switch (ret)
		{
		case QMessageBox::Yes:
			changeTableData(0, QPointF(0, 0));
			changeTableData(TB_Table->rowCount() - 1, QPointF(0.035, 0));
			clickRadioButton_RelativeVelocity();
			return;
		case QMessageBox::No:
			RB_RelativeVelocity->setChecked(false);
			return;
		}
	}
	QLineSeries* rv = vcht1->LineSeries()[RELATIVE_VELOCITY];
	/*QLineSeries**/QList<QPointF> nv = dataMap/*vcht0->LineSeries()*/[NOZZLE_VELOCITY];
	//QLineSeries* av = vcht0->LineSeries()[ARC_VELOCITY];
	double minv = DBL_MAX;
	double maxv = DBL_MIN;
	dataMap[RELATIVE_VELOCITY].clear();
	rv->clear();
	QList<QPointF> data;
	vcht0->MCHS()->calculate_curve(vcht0->ScatterSeries()[INTERPOLATION_POINT], data, 0.00001);
	data.push_back(QPointF(0.035, 0));
//	QPointF d0 = 
	//dataMap[RELATIVE_VELOCITY].push_back(QPointF(0.035, 0));
	int count = nv.size();
// 	if (data.size()/*dataMap[RELATIVE_VELOCITY].size()*/ != nv.size())
// 	{
// 		int ret = messageBox::run("The velocity profile of arc is incorrect.\nYou must determine the start and end points.", "Do you want to continue the process.\nProfile data will be changed to start(0, 0) and end(0.035, 0).", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
// 		switch (ret)
// 		{
// 			case QMessageBox::Yes:
// 				changeTableData(0, QPointF(0, 0));
// 				changeTableData(TB_Table->rowCount() - 1, QPointF(0.035, 0));
// 				clickRadioButton_RelativeVelocity();
// 				return;
// 			case QMessageBox::No:
// 				RB_RelativeVelocity->setChecked(false);
// 				return;
// 		}
// 	}
	//int j = 0;
	for (unsigned int i = 0; i < nv.size(); i++)
	{
		QPointF a = data/*dataMap[RELATIVE_VELOCITY]*/.at(i);
		QPointF n = nv.at(i);
		double dx = a.x() - n.x();
		double dy = a.y() - n.y();
		dataMap[RELATIVE_VELOCITY].push_back(QPointF(n.x(), dy));
		if (i % 10)
			continue;
		rv->append(n.x(), dy);
		if (dy > maxv)
			maxv = dy;
		if (dy < minv)
			minv = dy;
	}
	int sz = nv.size();
	QPointF last(nv.at(sz - 1).x(), data/*dataMap[RELATIVE_VELOCITY]*/.at(sz - 1).y());
	dataMap[RELATIVE_VELOCITY].push_back(last);
	rv->append(last);
	vcht1->setAxisRange(0, 0.035, minv, maxv);
	vcht1->setMinMax(RELATIVE_VELOCITY, 0, 0.035, minv, maxv);
	vcht1->LineSeries()[VELOCITY_RATIO]->hide();
	rv->show();
	_isChangeData = false;
}

void vp_profile::changeCellItem(QTableWidgetItem* item)
{
	if (!_isClicedCell)
		return;
	unsigned int x = item->row();
	unsigned int y = item->column();

	double v = item->text().toDouble();
	vcht0->changeSeriesValue(x, y, v);
	_isClicedCell = false;
	_isChangeData = true;
// 	if (RB_RelativeVelocity->isChecked())
// 		clickRadioButton_RelativeVelocity();
// 	else if (RB_VelocityRatio->isChecked())
// 		clickRadioButton_VelocityRatio();
}

void vp_profile::doubleClicked(QTableWidgetItem* item)
{
	_isClicedCell = true;
}

void vp_profile::exportData()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Export"), userPath + "untitled.bin", tr("profile data (*.bin)"));
	if (fileName.isEmpty())
		return;
	QList<QPointF> arcVel = vcht0->LineSeries()[ARC_VELOCITY]->pointsVector().toList();
	dataMap[ARC_VELOCITY] = arcVel;
	dataMap[INTERPOLATION_POINT] = vcht0->ScatterSeries()[INTERPOLATION_POINT]->pointsVector().toList();
	QFile qf(fileName);
	qf.open(QIODevice::WriteOnly);
	QMapIterator<int, QList<QPointF>> data(dataMap);
	int count = 0;
	int type = 0;
	while (data.hasNext())
	{
		data.next();
		count = data.value().size();
		type = data.key();
		if (count)
		{
			qf.write((char*)&count, sizeof(int));
			qf.write((char*)&type, sizeof(int));
			qf.write((char*)data.value().toVector().data(), sizeof(QPointF) * count);
		}
	}
// 	QMapIterator<int, QLineSeries*> ls(vcht0->LineSeries());
// 	
// 	while (ls.hasNext())
// 	{
// 		ls.next();
// 		int idx = ls.key();
// 		QLineSeries* series = ls.value();
// 		count = series->count();
// 		if (!count)
// 			continue;
// 		qf.write((char*)&count, sizeof(int));
// 		qf.write((char*)&idx, sizeof(int));
// 		qf.write((char*)series->pointsVector().data(), sizeof(QPointF) * series->count());
// 	}
// 	ls = vcht1->LineSeries();
// 	while (ls.hasNext())
// 	{
// 		ls.next();
// 		int idx = ls.key();
// 		QLineSeries* series = ls.value();
// 		count = series->count();
// 		if (!count)
// 			continue;
// 		qf.write((char*)&count, sizeof(int));
// 		qf.write((char*)&idx, sizeof(int));
// 		qf.write((char*)series->pointsVector().data(), sizeof(QPointF) * series->count());
// 	}
// 	QMapIterator<int, QScatterSeries*> ss(vcht0->ScatterSeries());
// 	while (ss.hasNext())
// 	{
// 		ss.next();
// 		int idx = ss.key();
// 		QScatterSeries* series = ss.value();
// 		count = series->count();
// 		if (!count)
// 			continue;
// 		qf.write((char*)&count, sizeof(int));
// 		qf.write((char*)&idx, sizeof(int));
// 		qf.write((char*)series->pointsVector().data(), sizeof(QPointF) * series->count());
// 	}
	
// 	char ch = '0';
// 	if (series->count())
// 	{
// 		/*ch = 'n';*/
// 		qf.write((char*), sizeof(char));
// 		qf.write((char*)series->pointsVector().data(), sizeof(QPointF) * series->count());
// 	}
	int loc = fileName.lastIndexOf('.');
	QString ascii_fileName = fileName.left(loc) + ".txt";
	vcht0->exportSplineData(ascii_fileName);
}

void vp_profile::importData()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("import"), userPath, tr("profile data (*.bin)"));
	if (fileName.isEmpty())
		return;
	QFile qf(fileName);
	qf.open(QIODevice::ReadOnly);
	QMapIterator<int, QLineSeries*> ls(vcht0->LineSeries());
	int count = 0;
	int idx = 0;
	while (!qf.atEnd())
	{
		qf.read((char*)&count, sizeof(int));
		QPointF* points = new QPointF[count];
		qf.read((char*)&idx, sizeof(int));
		qf.read((char*)points, sizeof(QPointF) * count);
		//QList<QPointF> list;
		dataMap[idx].clear();
		for (int i = 0; i < count; i++)
		{
			dataMap[idx].push_back(points[i]);
		}
		QPointF point;
		if (idx <= 3)
		{
			QLineSeries* ls = vcht0->LineSeries()[idx];
			ls->clear();
			for (int i = 0; i < count; i++)
			{
// 				if (i % 10)
// 					continue;
				point = points[i];
				ls->append(point.x(), point.y());
			}
				
		}
		else if (idx <= 5)
		{
			QLineSeries* ls = vcht1->LineSeries()[idx];
			ls->clear();
			for (int i = 0; i < count; i++)
			{
// 				if (i % 10)
// 					continue;
				ls->append(points[i]);
			}
				
		}
		else if (idx == 6)
		{
			QScatterSeries* ls = vcht0->ScatterSeries()[idx];
			ls->clear();
			for (int i = 0; i < count; i++)
			{
				ls->append(points[i]);
			}
			vcht0->setMCHS(count, points);
		}
		delete[] points;
	}
	changeSeries(0);
}

void vp_profile::changeSeries(int idx)
{
// 	CB_SeriesList->addItem("Arc stroke");
// 	CB_SeriesList->addItem("Arc velocity");
// 	CB_SeriesList->addItem("Arc acceleration");
// 	CB_SeriesList->addItem("Relative velocity");
// 	CB_SeriesList->addItem("Velocity ratio");
	QString str = CB_SeriesList->currentText();
	if (TB_Table->rowCount())
		TB_Table->clearContents();


	QScatterSeries *s_series = NULL;
	if (str == "Interpolation point")
	{
		TB_Table->setSelectionMode(QAbstractItemView::SingleSelection);
		s_series = vcht0->ScatterSeries()[INTERPOLATION_POINT];// <QLineSeries*>(vcht0->Chart()->series().at(1));
		for (unsigned int i = 0; i < s_series->count(); i++)
		{
			TB_Table->insertRow(i);
			TB_Table->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i)));
			TB_Table->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(s_series->at(i).x())));
			TB_Table->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(s_series->at(i).y())));
		}
		return;
	}

	QLineSeries* series = NULL;

	if (str == "Arc stroke")
	{
		TB_Table->setSelectionMode(QAbstractItemView::NoSelection);
		series = vcht0->LineSeries()[ARC_STROKE];
	}
	else if (str == "Nozzle velocity")
	{
		TB_Table->setSelectionMode(QAbstractItemView::NoSelection);
		series = vcht0->LineSeries()[NOZZLE_VELOCITY];
	}
	else if (str == "Arc velocity")
	{
		TB_Table->setSelectionMode(QAbstractItemView::NoSelection);
		series = vcht0->LineSeries()[ARC_VELOCITY];
	}
	else if (str == "Arc acceleration")
	{
		TB_Table->setSelectionMode(QAbstractItemView::NoSelection);
		series = vcht0->LineSeries()[ARC_ACCELERATION];
	}
	else if (str == "Relative velocity")
	{
		TB_Table->setSelectionMode(QAbstractItemView::NoSelection);
		series = vcht1->LineSeries()[RELATIVE_VELOCITY];
	}
	else if (str == "Velocity ratio")
	{
		TB_Table->setSelectionMode(QAbstractItemView::NoSelection);
		series = vcht1->LineSeries()[VELOCITY_RATIO];
	}
	for (unsigned int i = 0; i < series->count(); i++)
	{
		TB_Table->insertRow(i);
		TB_Table->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i)));
		TB_Table->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(series->at(i).x())));
		TB_Table->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(series->at(i).y())));
	}
}

void vp_profile::clickRadioButton_VelocityRatio()
{
	bool chk = checkFirstEndData();
	if (!chk)
	{
		int ret = messageBox::run("The velocity profile of arc is incorrect.\nYou must determine the start and end points.", "Do you want to continue the process.\nProfile data will be changed to start(0, 0) and end(0.035, 0).", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		switch (ret)
		{
		case QMessageBox::Yes:
			changeTableData(0, QPointF(0, 0));
			changeTableData(TB_Table->rowCount() - 1, QPointF(0.035, 0));
			clickRadioButton_VelocityRatio();
			return;
		case QMessageBox::No:
			RB_RelativeVelocity->setChecked(false);
			return;
		}
	}
	QLineSeries* vr = vcht1->LineSeries()[VELOCITY_RATIO];
	//QLineSeries* nv = vcht0->LineSeries()[NOZZLE_VELOCITY];
	/*QLineSeries**/QList<QPointF> nv = dataMap/*vcht0->LineSeries()*/[NOZZLE_VELOCITY];
	//QLineSeries* av = vcht0->LineSeries()[ARC_VELOCITY];
	double minv = DBL_MAX;
	double maxv = DBL_MIN;
	dataMap[VELOCITY_RATIO].clear();
	vr->clear();
	QList<QPointF> data;
	vcht0->MCHS()->calculate_curve(vcht0->ScatterSeries()[INTERPOLATION_POINT], data/*Map[VELOCITY_RATIO]*/, 0.00001);
	data/*Map[VELOCITY_RATIO]*/.push_back(QPointF(0.035, 0));
	//int count = av->count();
//	qDebug() << "Velocity ratio size : [" << rdata.size() << ", " << nv->count() << "]";
// 	if (data/*Map[VELOCITY_RATIO]*/.size() != nv.size())
// 	{
// 		int ret = messageBox::run("The velocity profile of arc is incorrect.\nYou must determine the start and end points.", "Do you want to continue the process.\nProfile data will be changed to start(0, 0) and end(0.035, 0).", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
// 		switch (ret)
// 		{
// 		case QMessageBox::Yes:
// 			changeTableData(0, QPointF(0, 0));
// 			changeTableData(TB_Table->rowCount() - 1, QPointF(0.035, 0));
// 			clickRadioButton_VelocityRatio();
// 			return;
// 		case QMessageBox::No:
// 			RB_VelocityRatio->setChecked(false);
// 			return;
// 		}
// 	}
	//int j = 0;
	for (unsigned int i = 0; i < nv.size(); i++)
	{
	
		QPointF a = data/*Map[VELOCITY_RATIO]*/.at(i);
		QPointF n = nv.at(i);
		double dx = a.x() - n.x();
// 		if (dx > 1e-9)
// 			continue;
// 		j++;
		double ratio = abs(a.y()) / abs(n.y());
		dataMap[VELOCITY_RATIO].push_back(QPointF(n.x(), ratio));
		if (i % 10)
			continue;
		vr->append(n.x(), ratio);
		if (ratio > maxv)
			maxv = ratio;
		if (ratio < minv)
			minv = ratio;
	}
	int sz = nv.size();
	QPointF last(nv.at(sz - 1).x(), data/*Map[VELOCITY_RATIO]*/.at(sz - 1).y());
	dataMap[VELOCITY_RATIO].push_back(last);
	vr->append(last.x(), last.y());
	vcht1->setAxisRange(0, 0.035, 0, 1.0);
	vcht1->setMinMax(VELOCITY_RATIO, 0, 0.035, 0, 1.0);
	vcht1->LineSeries()[RELATIVE_VELOCITY]->hide();
	vr->show();
}
