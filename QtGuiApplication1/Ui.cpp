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
		//adaugam observere pt ctrl,wish si intre ele
		auto cl =new ClientMenu(ctrl);
		ctrl.addObserver(cl);
		ctrl.addWishObserver(cl);
		cl->exec();
		cl->update();
		clients.push_back(cl); 
		//adaugam observere la read only
		if (clients.size()==1)
		for (auto& v : views)
			cl->addObserver(v);
	});


	QObject::connect(welcome.adminMenu, &QPushButton::clicked, [this]() {admin.exec(); });


	QObject::connect(welcome.clientViewOnlyMenu,&QPushButton::clicked,[this](){
		auto v = new ViewWishList(ctrl.wishList);
		if (clients.size()>=1)
		clients[0]->addObserver(v);
		v->exec();
		views.push_back(v);
	});

}