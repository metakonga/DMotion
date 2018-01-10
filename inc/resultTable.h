#ifndef RESULTTABLE_H
#define RESULTTABLE_H

#include <QWidget>
#include <QModelIndex>
#include "dmotion_types.h"

QT_BEGIN_NAMESPACE
class QTableWidget;
class QTableWidgetItem;
QT_END_NAMESPACE

class optimumDesignDoc;

class resultTable : public QWidget
{
	Q_OBJECT

public:
	resultTable(optimumDesignDoc* _odd, QWidget *parent = 0);
	~resultTable();

	void reset();
	void setTable(stResultSet& ref_result, algebra::vector<stResultSet> &results);
	//void appendTable(stResultSet& result);
	void appendTable(QString _name, QList<double>& list);
	QTableWidget* ResultTable();
	//void resetTable() { ptable->clearContents(); }
	//void setTable(vector3f* data, std::map<QString, particleObject> *particleObjects);
	private slots:
	void actionClick(QModelIndex);


private:
	QTableWidget *rtable;
	optimumDesignDoc *odd;
};

#endif