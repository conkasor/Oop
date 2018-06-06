#include "Model.h"

int Model::rowCount(const QModelIndex &parent) const
{
	return stringList.count();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= stringList.size())
		return QVariant();

	if (role == Qt::DisplayRole)
		return stringList.at(index.row());
	else
		return QVariant();
}

