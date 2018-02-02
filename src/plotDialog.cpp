#include "plotDialog.h"
#include "model.h"
#include "callout.h"
#include "columnViewItem.h"
#include <QLineSeries>
#include <QtWidgets>
#include <QtCharts>

#include <QtGui>
//#include <QtGui/QMouseEvent>

plotDialog::plotDialog(QWidget* parent /* = NULL */)
	: QMainWindow(parent)
	, xSize(700)
	, ySize(600)
	, openColumnCount(1)
	, wWidth(0)
	, wHeight(0)
	, vcht(NULL)
	, md(NULL)
	, cview(NULL)
	, cmodel(NULL)
	, m_tooltip(NULL)
{
	QFrame *vb = new QFrame(this);
	QVBoxLayout *layout = new QVBoxLayout(vb);
	layout->setMargin(0);
	vb->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	//Chart *cht = new Chart();
	cview = new QColumnView(this);
	cview->setMinimumHeight(100);
	cview->setMaximumHeight(100);
	vcht = new chartView(this);
	setMinimumSize(640, 580);
	resize(xSize, ySize);
//	QHBoxLayout *h_layout = new QHBoxLayout;
	layout->addWidget(vcht);
	layout->addWidget(cview);
	setCentralWidget(vb);
	//cht->resize(this->size());
}

plotDialog::~plotDialog()
{
	if (cmodel) delete cmodel; cmodel = NULL;
	if (cview) delete cview; cview = NULL;
	if (vcht) delete vcht; vcht = NULL;
}

void plotDialog::clicked(QModelIndex index)
{
	QStandardItem* item = cmodel->itemFromIndex(index);
	QString str;
	if (item->hasChildren())
	{
		openColumnCount++;
		QStandardItem* child = item->child(0);
		str = child->text();
	}
	else
	{
		QStandardItem* obj = item->parent();
		QStandardItem* rcf = obj->parent();
		
		QLineSeries *series = new QLineSeries;
		QString s_name = obj->text() + "_" + item->text();//series->setName(obj->text());
		double x_max = FLT_MIN;
		double x_min = FLT_MAX;
		double y_max = FLT_MIN;
		double y_min = FLT_MAX;
		if (rcf->text() == "Rigid body")
		{
			QVector<resultDataType> *datas = md->bodyResultData(obj->text());
			QVectorIterator<resultDataType> data(*datas);
			if (item->text() == "PX") { s_name += " (m)"; }
			else if (item->text() == "PY") { s_name += " (m)"; }
			else if (item->text() == "TR") { s_name += " (rad)"; }
			else if (item->text() == "VX") { s_name += " (m/s)"; }
			else if (item->text() == "VY") { s_name += " (m/s)"; }
			else if (item->text() == "TV") { s_name += " (rad/s)"; }
			else if (item->text() == "AX") { s_name += " (m/s^2)"; }
			else if (item->text() == "AY") { s_name += " (m/s^2)"; }
			else if (item->text() == "TA") { s_name += " (rad/s^2)"; }
			while (data.hasNext())
			{
				resultDataType rdt = data.next();
				double t = rdt.time;
				double v = 0;
				x_min = t < x_min ? t : x_min;
				x_max = t > x_max ? t : x_max;
				if (item->text() == "PX") { v = rdt.pos.X(); }
				else if (item->text() == "PY") { v = rdt.pos.Y(); }
				else if (item->text() == "TR") { v = rdt.ang; }
				else if (item->text() == "VX") { v = rdt.vel.X(); }
				else if (item->text() == "VY") { v = rdt.vel.Y(); }
				else if (item->text() == "TV") { v = rdt.angv; }
				else if (item->text() == "AX") { v = rdt.acc.X(); }
				else if (item->text() == "AY") { v = rdt.acc.Y(); }
				else if (item->text() == "TA") { v = rdt.anga; }
				y_min = v < y_min ? v : y_min;
				y_max = v > y_max ? v : y_max;
				series->append(t, v);
			}
		}
		else if (rcf->text() == "Joint")
		{
			QVector<jointResultDataType> *datas = md->jointResultData(obj->text());
			QVectorIterator<jointResultDataType> data(*datas);
			s_name += " (N)";
			while (data.hasNext())
			{
				jointResultDataType jrdt = data.next();
				double t = jrdt.time;
				double v = 0;
				x_min = t < x_min ? t : x_min;
				x_max = t > x_max ? t : x_max;
				if (item->text() == "FM Reaction force") v = jrdt.tr;
				else if (item->text() == "FX Reaction force") v = jrdt.fx;
				else if (item->text() == "FY Reaction force") v = jrdt.fy;
// 				else if (item->text() == "TM Reaction force") v = jrdt.rm;
// 				else if (item->text() == "TX Reaction force") v = jrdt.rx;
// 				else if (item->text() == "TY Reaction force") v = jrdt.ry;
				
				y_min = v < y_min ? v : y_min;
				y_max = v > y_max ? v : y_max;
				series->append(t, v);
			}
		}
		double t = (y_max - y_min) * 0.1;
		series->setName(s_name);
		vcht->addSeries(series);
		vcht->setAxisRange(x_min, x_max, y_min - t, y_max + t);
	}
}

void plotDialog::setBodyRoot(QStandardItem *o)
{
	QStandardItem *px = new QStandardItem("PX");
	QStandardItem *py = new QStandardItem("PY");
	QStandardItem *th = new QStandardItem("TR");
	QStandardItem *vx = new QStandardItem("VX");
	QStandardItem *vy = new QStandardItem("VY");
	QStandardItem *dth = new QStandardItem("TV");
	QStandardItem *ax = new QStandardItem("AX");
	QStandardItem *ay = new QStandardItem("AY");
	QStandardItem *ddth = new QStandardItem("TA");
	o->appendRow(px); o->appendRow(py); o->appendRow(th);
	o->appendRow(vx); o->appendRow(vy); o->appendRow(dth);
	o->appendRow(ax); o->appendRow(ay); o->appendRow(ddth);
	
}

void plotDialog::setJointForceRoot(QStandardItem *o)
{
	QStandardItem *FM = new QStandardItem("FM Reaction force");
	QStandardItem *FX = new QStandardItem("FX Reaction force");
	QStandardItem *FY = new QStandardItem("FY Reaction force");
	QStandardItem *TM = new QStandardItem("TM Reaction force");
	QStandardItem *TX = new QStandardItem("TX Reaction force");
	QStandardItem *TY = new QStandardItem("TY Reaction force");
	o->appendRow(FM);
	o->appendRow(FX);
	o->appendRow(FY);
	o->appendRow(TM);
	o->appendRow(TX);
	o->appendRow(TY);
}

void plotDialog::setModel(model* _md)
{
	md = _md;
	if (cmodel)
		return;
	cmodel = new QStandardItemModel;
	
	//unsigned int ncol = md->RigidBodies().size();
	QStandardItem *g_model = new QStandardItem(md->ModelName());
	QStandardItem *r_body = new QStandardItem("Rigid body");
	QStandardItem *b_joint = new QStandardItem("Joint");
	//QStandardItem *r_joint = new QStandardItem("Joint");
	cmodel->appendRow(g_model);
	//QList<QStandardItem*> g_object;
	g_model->appendRow(r_body);
	g_model->appendRow(b_joint);
	QMapIterator<QString, rigidBody*> bodies = md->RigidBodies();
	while (bodies.hasNext())
	{
		rigidBody *rb = bodies.next().value();
		QStandardItem *o = new QStandardItem(rb->Name());
		r_body->appendRow(o);
		setBodyRoot(o);
	}
	QMapIterator<QString, constraint*> cons = md->Constraints();
// 	QStandardItem *react = new QStandardItem("Reaction");
// 	->appendRow(react);
	while (cons.hasNext())
	{
		constraint* c = cons.next().value();
		QStandardItem *o = new QStandardItem(c->Name());
		b_joint->appendRow(o);
		setJointForceRoot(o);
	}
	cview->setModel(cmodel);
	connect(cview, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked(QModelIndex)));
}

void plotDialog::columnViewAdjustSameSize(int ncol)
{
// 	QList<int> newSize;
// 	
// 	int each = static_cast<int>((1.0 / static_cast<double>(ncol)) * wWidth) + 1;
// 	for (int i = 0; i < ncol; i++)
// 	{
// 		newSize.push_back(each);
// 	}
// 	cview->setColumnWidths(newSize);
// 	int each_width = 0.2 * wWidth;
// 	QList<int> newWidth;
// 	//int cc = cview->model()->columnCount();
// 	newWidth.push_back(each_width);
// 	newWidth.push_back(each_width);
// 	newWidth.push_back(each_width);
// 	newWidth.push_back(each_width);
// 	newWidth.push_back(each_width);
// 	//newWidth.push_back(each_width);
// 	cview->setColumnWidths(newWidth);
}

void plotDialog::resizeEvent(QResizeEvent *event)
{
// 	wWidth = event->size().width();
// 	wHeight = event->size().height();
// 	int each_width = 0.2 * wWidth;
// 	QList<int> newWidth;
// 	//int cc = cview->model()->columnCount();
// 	newWidth.push_back(each_width);
// 	newWidth.push_back(each_width);
// 	newWidth.push_back(each_width);
// 	newWidth.push_back(each_width);
// 	newWidth.push_back(each_width);
// 	//newWidth.push_back(each_width);
// 	cview->setColumnWidths(newWidth);
}