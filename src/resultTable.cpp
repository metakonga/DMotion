#include "resultTable.h"
#include "MyTableWidgetItem.h"
#include "document.h"
#include "DMotion.h"
#include "optimumDesignDoc.h"
#include <QtWidgets>

resultTable::resultTable(optimumDesignDoc* _odd, QWidget *parent) 
	: QWidget(parent)
	, odd(_odd)
{
	rtable = new QTableWidget(0, 2 + _odd->ReactionListSize());
	rtable->setSelectionBehavior(QAbstractItemView::SelectRows);

	QStringList labels;
	labels << "ID" << "Case"; 
	QMapIterator<reactionForceType, bool> list(_odd->SelectList());
	while (list.hasNext())
	{
		list.next();
		QString str = ReactionForceTypeStringByIndex(list.key());
		labels << str;
	}
	//<< "Nozzel Trans.(FY)" << "Nozzel Trans.(TZ)" << "Nozzel-Link Rev.(FX)" << "Nozzel-Link Rev.(FY)" << "Link-Cam Rev.(FX)" << "Link-Cam Rev.(FY)" << "Cam-Ground Rev.(FX)" << "Cam-Ground Rev.(FY)" << "Arc Trans.(FY)" << "Arc Trans.(TZ)" << "Arc-Cam PF(FX)" << "Arc-Cam PF(FY)";
	rtable->setHorizontalHeaderLabels(labels);
	rtable->verticalHeader()->hide();
	rtable->setShowGrid(true);
	//rtable->setSortingEnabled(true);
	//rtable->setCop
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
	mainLayout->addWidget(rtable, 0, 0);
	setLayout(mainLayout);
	setWindowTitle(tr("Result table"));
	resize(700, 300);
	setWindowModality(Qt::WindowModality::ApplicationModal);

	connect(rtable, SIGNAL(clicked(QModelIndex)), this, SLOT(actionClick(QModelIndex)));
}

resultTable::~resultTable()
{
	
	if (rtable)
	{
		for (unsigned int i = 0; i < rtable->rowCount(); i++)
		{
			for (unsigned int j = 0; j < rtable->columnCount(); j++)
			{
				delete rtable->item(i, j);
			}
		}
		rtable->clearContents();
		delete rtable; rtable = NULL;
	}
}

void resultTable::reset()
{
	rtable->setSortingEnabled(false);
	rtable->clearContents();
	rtable->setRowCount(0);
}

void resultTable::actionClick(QModelIndex index)
{
	int row = index.row();
	int col = index.column();
	QString caseName = rtable->item(row, 1)->text();
	odd->setSelectedCase(caseName);
	optimumCase* oc = odd->SelectedCase();
	QMap<QString, Handle(AIS_Shape)> hps = DMotion::getDocument()->getHardPoints();
	QMapIterator<QString, Handle(AIS_Shape)> ais(hps);
	while (ais.hasNext())
	{
		ais.next();
		QString hpName = ais.key();
		Handle(AIS_Shape) shape = ais.value();
		vecd3 loc0 = oc->HardPointsResults()[hpName].at(0);
		gp_Trsf t;
		t.SetTranslation(1000.0 * gp_Vec(loc0.X(), loc0.Y(), 0.0));
		shape->SetLocalTransformation(t);
	}
	DMotion::getApplication()->setCaseResult();
	DMotion::getAISContext()->UpdateCurrentViewer();
}

void resultTable::setTable(stResultSet &ref_result, algebra::vector<stResultSet> &results)
{
// 	rtable->setSortingEnabled(false);
// 	rtable->clearContents();
// 	rtable->setRowCount(0);
// 
// 	unsigned int row = 0;
// 	unsigned int i = 0;
// 	QString str;
// 	QTextStream(&str) << i;  MyTableWidgetItem *ID = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.N;  MyTableWidgetItem *N = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.D;  MyTableWidgetItem *D = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.d;  MyTableWidgetItem *d = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.FreeLength;  MyTableWidgetItem *FreeLength = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.k;  MyTableWidgetItem *k = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.Mass;  MyTableWidgetItem *Mass = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.B_Height;  MyTableWidgetItem *B_Height = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.P;  MyTableWidgetItem *P = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.P_BH;  MyTableWidgetItem *P_BH = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.Sc;  MyTableWidgetItem *Sc = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.Sc_BH;  MyTableWidgetItem *Sc_BH = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.PE_act;  MyTableWidgetItem *PE_act = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.Efficiency;  MyTableWidgetItem *Efficiency = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.transferEnergy;  MyTableWidgetItem *transferEnergy = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.v_ep;  MyTableWidgetItem *v_ep = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.C;  MyTableWidgetItem *C = new MyTableWidgetItem(str); str.clear();
// 	QTextStream(&str) << ref_result.AR;  MyTableWidgetItem *AR = new MyTableWidgetItem(str); str.clear();
// 
// 	rtable->insertRow(row);
// 	rtable->setItem(row, 0, ID);
// 	rtable->setItem(row, 1, N);
// 	rtable->setItem(row, 2, D);
// 	rtable->setItem(row, 3, d);
// 	rtable->setItem(row, 4, FreeLength);
// 	rtable->setItem(row, 5, k);
// 	rtable->setItem(row, 6, Mass);
// 	rtable->setItem(row, 7, B_Height);
// 	rtable->setItem(row, 8, P);
// 	rtable->setItem(row, 9, P_BH);
// 	rtable->setItem(row, 10, Sc);
// 	rtable->setItem(row, 11, Sc_BH);
// 	rtable->setItem(row, 12, PE_act);
// 	rtable->setItem(row, 13, Efficiency);
// 	rtable->setItem(row, 14, transferEnergy);
// 	rtable->setItem(row, 15, v_ep);
// 	rtable->setItem(row, 16, C);
// 	rtable->setItem(row, 17, AR);
// 	row++;
// 	for (unsigned int i = 0; i < results.sizes(); i++){
// 		resultSet result = results(i);
// 
// 		QTextStream(&str) << i + 1;  MyTableWidgetItem *ID = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.N;  MyTableWidgetItem *N = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.D;  MyTableWidgetItem *D = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.d;  MyTableWidgetItem *d = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.FreeLength;  MyTableWidgetItem *FreeLength = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.k;  MyTableWidgetItem *k = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.Mass;  MyTableWidgetItem *Mass = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.B_Height;  MyTableWidgetItem *B_Height = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.P;  MyTableWidgetItem *P = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.P_BH;  MyTableWidgetItem *P_BH = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.Sc;  MyTableWidgetItem *Sc = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.Sc_BH;  MyTableWidgetItem *Sc_BH = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.PE_act;  MyTableWidgetItem *PE_act = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.Efficiency;  MyTableWidgetItem *Efficiency = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.transferEnergy;  MyTableWidgetItem *transferEnergy = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.v_ep;  MyTableWidgetItem *v_ep = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.C;  MyTableWidgetItem *C = new MyTableWidgetItem(str); str.clear();
// 		QTextStream(&str) << result.AR;  MyTableWidgetItem *AR = new MyTableWidgetItem(str); str.clear();
// 
// 		rtable->insertRow(row);
// 		rtable->setItem(row, 0, ID);
// 		rtable->setItem(row, 1, N);
// 		rtable->setItem(row, 2, D);
// 		rtable->setItem(row, 3, d);
// 		rtable->setItem(row, 4, FreeLength);
// 		rtable->setItem(row, 5, k);
// 		rtable->setItem(row, 6, Mass);
// 		rtable->setItem(row, 7, B_Height);
// 		rtable->setItem(row, 8, P);
// 		rtable->setItem(row, 9, P_BH);
// 		rtable->setItem(row, 10, Sc);
// 		rtable->setItem(row, 11, Sc_BH);
// 		rtable->setItem(row, 12, PE_act);
// 		rtable->setItem(row, 13, Efficiency);
// 		rtable->setItem(row, 14, transferEnergy);
// 		rtable->setItem(row, 15, v_ep);
// 		rtable->setItem(row, 16, C);
// 		rtable->setItem(row, 17, AR);
// 		row++;
// 	}
// 	//rtable->sortByColumn(0, Qt::SortOrder::AscendingOrder);
// 	rtable->setSortingEnabled(true);
}

//void resultTable::appendTable(stResultSet& result)
// {
// 	unsigned int row = rtable->rowCount();
// 	MyTableWidgetItem *ID = new MyTableWidgetItem(QString("%1").arg(row));
// 	MyTableWidgetItem *caseName = new MyTableWidgetItem(result.caseName);
// 	MyTableWidgetItem *AT_FY = new MyTableWidgetItem(QString("%1").arg(result.AT_FY));
// 	MyTableWidgetItem *AT_TR = new MyTableWidgetItem(QString("%1").arg(result.AT_TR));
// 	MyTableWidgetItem *ALR_FX = new MyTableWidgetItem(QString("%1").arg(result.ALR_FX));
// 	MyTableWidgetItem *ALR_FY = new MyTableWidgetItem(QString("%1").arg(result.ALR_FY));
// 	MyTableWidgetItem *LCR_FX = new MyTableWidgetItem(QString("%1").arg(result.LCR_FX));
// 	MyTableWidgetItem *LCR_FY = new MyTableWidgetItem(QString("%1").arg(result.LCR_FY));
// 	MyTableWidgetItem *CGR_FX = new MyTableWidgetItem(QString("%1").arg(result.CGR_FX));
// 	MyTableWidgetItem *CGR_FY = new MyTableWidgetItem(QString("%1").arg(result.CGR_FY));
// 	MyTableWidgetItem *PT_FY = new MyTableWidgetItem(QString("%1").arg(result.PT_FY));
// 	MyTableWidgetItem *PT_TR = new MyTableWidgetItem(QString("%1").arg(result.PT_TR));
// 	MyTableWidgetItem *PF_FX = new MyTableWidgetItem(QString("%1").arg(result.PF_FX));
// 	MyTableWidgetItem *PF_FY = new MyTableWidgetItem(QString("%1").arg(result.PF_FY));
// 	rtable->insertRow(row);
// 	rtable->setItem(row, 0, ID);
// 	rtable->setItem(row, 1, caseName);
// 	rtable->setItem(row, 2, AT_FY);
// 	rtable->setItem(row, 3, AT_TR);
// 	rtable->setItem(row, 4, ALR_FX);
// 	rtable->setItem(row, 5, ALR_FY);
// 	rtable->setItem(row, 6, LCR_FX);
// 	rtable->setItem(row, 7, LCR_FY);
// 	rtable->setItem(row, 8, CGR_FX);
// 	rtable->setItem(row, 9, CGR_FY);
// 	rtable->setItem(row, 10, PT_FY);
// 	rtable->setItem(row, 11, PT_TR);
// 	rtable->setItem(row, 12, PF_FX);
// 	rtable->setItem(row, 13, PF_FY);
// }

void resultTable::appendTable(QString _name, QList<double>& list)
{
	unsigned int row = rtable->rowCount();
	MyTableWidgetItem *ID = new MyTableWidgetItem(QString("%1").arg(row));
	MyTableWidgetItem *caseName = new MyTableWidgetItem(_name);
	int col = 0;
	rtable->insertRow(row);
	rtable->setItem(row, col++, ID);
	rtable->setItem(row, col++, caseName);
	foreach(double val, list)
	{
		MyTableWidgetItem *item = new MyTableWidgetItem(QString("%1").arg(val));
		rtable->setItem(row, col++, item);
	}
}

QTableWidget* resultTable::ResultTable()
{
	return rtable;
}
