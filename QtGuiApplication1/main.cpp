#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include<QListWidget>
#include <QListWidgetItem>
#include <qwidget.h>
#include <QVBoxLayout>
#include<QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QObject>
#include <QListWidget>
#include "Greetings.h"
#include"clientMenu.h"
#include "Ui.h"
#include <qdebug.h>
#include "Controller.h"

void f(QWidget* w) {
	w->show();
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Repo rep;
	ValidatorOferte val;
	WishList wish;
	Controller ctr(rep, val, wish);
	Ui ui(ctr);
	ui.start();
	return app.exec();
}