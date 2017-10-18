#include "columnViewItem.h"

columnViewItem::columnViewItem()
	: QAbstractItemModel()
{
	connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(clickItem(QModelIndex)));
}

columnViewItem::~columnViewItem()
{

}

void columnViewItem::clickItem(const QModelIndex &index)
{

}