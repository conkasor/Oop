#include "Ui.h"
#include<QListWidget>
#include <QListWidgetItem>
#include <qwidget.h>
#include <QVBoxLayout>
#include<QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QObject>
#include <QListWidget>
#include <QVBoxLayout>
#include "Greetings.h"
#include "clientMenu.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include<qdebug.h>
#include "clientMenu.h"
void Ui::start()
{
	welcome.exec();
	connects();
}

void Ui::connects() {
	QObject::connect(welcome.clientMenu, &QPushButton::clicked, [this]() {
		//adaugam observere pt repo,wish si intre ele
		auto cl = new ClientMenu(ctrl);
		ctrl.addObserver(cl);
		ctrl.addWishObserver(cl);
		cl->exec();
		cl->update();
		clients.push_back(cl);
	});

	QObject::connect(welcome.adminMenu, &QPushButton::clicked, [this]() {admin.exec(); });

	QObject::connect(welcome.clientViewOnlyMenu, &QPushButton::clicked, [this]() {
		auto v = new ViewWishList(ctrl.wishList);
		ctrl.wishList.addObserver(v);
		v->exec();
		views.push_back(v);
	});
}