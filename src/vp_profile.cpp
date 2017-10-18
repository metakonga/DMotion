#include "vp_profile.h"
#include <QLineSeries>
#include <QtWidgets>
#include <QtCharts>
//#include <QAbstractAxis>

vp_profile::vp_profile(QWidget* parent)
	: QDialog(parent)
	, vcht(NULL)
	, xSize(400)
	, ySize(300)
{
 	//Chart *cht = new Chart();
	vcht = new chartView(this);
	vcht->setChartMode(chartView::REALTIME_EDIT_CHART);
	table = new QTableWidget(0, 3);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	QStringList labels;
	labels << "ID" << "X Data" << "Y Data";
	table->setHorizontalHeaderLabels(labels);
	table->verticalHeader()->hide();
	table->setShowGrid(true);
	table->horizontalHeader()->setDefaultSectionSize(70);
	table->setMinimumWidth(210);
	table->setMaximumWidth(210);
	//table->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
	//vcht->chart()->legend()->hide();
  	//vcht->chart()->setTitle("Velocity profile");
	vcht->setTableWidget(table);
	resize(xSize, ySize);
	connect(this, SIGNAL(finished(int)), this, SLOT(finishDialog(int)));
	//vcht->resize(400, 300);
	QHBoxLayout *h_layout = new QHBoxLayout;
	h_layout->addWidget(vcht);
	h_layout->addWidget(table);
	setLayout(h_layout);
}

vp_profile::~vp_profile()
{
	if (table){
		table->clearContents();
		delete table; table = NULL;
	}
}

void vp_profile::finishDialog(int result)
{
	xSize = width();
	ySize = height();
}