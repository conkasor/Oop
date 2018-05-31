#pragma once
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
#include "Controller.h"

class Welcome :public QWidget {
	QFormLayout *fl = new QFormLayout(this);

public:
	QPushButton * clientMenu = new QPushButton("Client");
	QPushButton *adminMenu = new QPushButton("Admin");
	QPushButton* clientViewOnlyMenu = new QPushButton("Client View Only");
	QLabel *greetings = new QLabel("Dumneavoastra sunteti:");
	void exec();
};