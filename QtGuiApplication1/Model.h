#pragma once
#include <string>
#include <QAbstractListModel>
#include <vector>
#include "Oferta.h"
#include <QVariant>
#include <qvector.h>
#include <qstringlist.h>

class Model:public QAbstractListModel
{
	Q_OBJECT

private:
	QStringList stringList;
public:
	Model(const QStringList &strings, QObject *parent = 0)
		: QAbstractListModel(parent), stringList(strings) {}
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;

};
