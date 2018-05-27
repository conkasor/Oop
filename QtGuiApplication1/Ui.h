
#pragma once
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include<QListWidget>
#include <qobject.h>
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
#include "Admin.h"
#include "Observer.h"
#include <vector>
#include "ViewWishList.h"
class Ui
{
	Controller& ctrl;
	Welcome welcome;
	std::vector<ClientMenu*>clients;
	Admin admin;
	std::vector<ViewWishList*>views;


public:
	Ui(Controller& ctrl) :ctrl{ ctrl }, admin { ctrl } {
		admin.importFF();
	};
	
	void start();
	void connects();
};
