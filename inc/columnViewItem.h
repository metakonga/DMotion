#ifndef COLUMNVIEWITEM_H
#define COLUMNVIEWITEM_H

#include <QAbstractItemModel>

class columnViewItem : public QAbstractItemModel
{
	//Q_OBJECT

public:
	columnViewItem();
	~columnViewItem();

	private slots:
	void clickItem(const QModelIndex &index);
};

#endif