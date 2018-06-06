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
#include <QVBoxLayout>
#include "Greetings.h"
#include <qcombobox.h>
#include "Controller.h"
#include <qstatusbar.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qmenu.h>
#include <qimage.h>
#include <qshortcut.h>
#include <qsound.h>
#include <qmediaplayer.h>
#include "Observer.h"
#include "clientMenu.h"

class Admin :public QMainWindow
{
	Q_OBJECT;
	Controller& ctrl;

public:
	Admin(Controller& ctrl) :ctrl{ ctrl } {
		filterCB->addItem("Filter");
		filterCB->addItem("By Price");
		filterCB->addItem("By Destionation");
		filterCB->addItem("Unfilter");
		sortCB->addItem("Sort");
		sortCB->addItem("By Name");
		sortCB->addItem("By Destination");
		sortCB->addItem("By Type/Price");
	};
	QWidget* all = new QWidget();
	QWidget * wModifyForm = new QWidget();
	QMediaPlayer* sound = new QMediaPlayer();
	QWidget* wModifyButtons = new QWidget();
	QWidget* wModifyMenu = new QWidget();
	QPixmap* myImage = new QPixmap();
	QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), all);
	QShortcut *shortcut1 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), all);

	QLabel* imgLabel = new QLabel(wModifyMenu);
	QFormLayout* modifyForm = new QFormLayout(wModifyForm);
	QHBoxLayout* modifyButtons = new QHBoxLayout(wModifyButtons);
	QVBoxLayout* modifyMenuT = new QVBoxLayout(wModifyMenu);
	///

	QWidget* wMenu = new QWidget();
	QWidget* wButtons = new QWidget();
	QWidget* wImpExp = new QWidget();
	QWidget* wFileForm = new QWidget();
	QVBoxLayout* menu = new QVBoxLayout(wMenu);
	QHBoxLayout* buttons = new QHBoxLayout(wButtons);
	QHBoxLayout* frow = new QHBoxLayout(all);
	QHBoxLayout* impExp = new QHBoxLayout(wImpExp);
	QPushButton* importB = new QPushButton("Import");
	QPushButton* exportB = new QPushButton("Export", wImpExp);
	QFormLayout* formFile = new QFormLayout(wFileForm);
	QLineEdit* fileEdit = new QLineEdit();
	QLabel*	fileLabel = new QLabel();

	//general
	QListView * l1 = new QListView();
	
	QWidget* wFilterForm = new QWidget();
	QComboBox* sortCB = new QComboBox(wButtons);
	QComboBox* filterCB = new QComboBox(wButtons);
	QFormLayout* filterForm = new QFormLayout(wFilterForm);
	QLineEdit* filterEdit = new QLineEdit(wButtons);
	QPushButton* undoB = new QPushButton("Undo", wButtons);
	QPushButton* exportHtmlB = new QPushButton("Export to Html", wButtons);

	//

	//
	QLabel *lName = new QLabel("Name:", wModifyForm);
	QLineEdit* eName = new QLineEdit(wModifyForm);
	QLabel *lDest = new QLabel("Destination:", wModifyForm);
	QLineEdit* eDest = new QLineEdit(wModifyForm);
	QLabel *lType = new QLabel("Type:", wModifyForm);
	QLineEdit* eType = new QLineEdit(wModifyForm);
	QLabel *lPrice = new QLabel("Price:", wModifyForm);
	QLineEdit* ePrice = new QLineEdit(wModifyForm);
	QPushButton* addB = new QPushButton("add", wModifyButtons);
	QPushButton* deleteB = new QPushButton("del", wModifyButtons);
	QPushButton* changeB = new QPushButton("change", wModifyButtons);
	QPushButton* getB = new QPushButton("find", wModifyButtons);
	QStatusBar * statusBar = new QStatusBar(all);

	void exec();
	void connects();
	void populateFromVector(QListView& l, std::vector<Oferta>& v);
	void add();

	void del();

	void change() {
		std::string name = eName->text().toStdString();
		int iprice;

		std::string dest = eDest->text().toStdString();
		std::string type = eType->text().toStdString();
		std::string price = ePrice->text().toStdString();
		try {
			iprice = std::stoi(price);
			ctrl.change(name, dest, type, iprice);
			statusBar->showMessage("Offer changed!");
		}
		catch (RepoException& e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
		catch (ValidateException&e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
		catch (CtrlException&e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
		catch (exception) { statusBar->showMessage("Invalid Price!"); };
	}

	void get(std::string name);

	void sortByName();

	void sortByDest();

	void sortTypePrice();

	void notify();

	void filterByDest();

	void filterByPrice();

	void populateAll();

	void doUndo();

	void toHtml();

	void importFF();

	void exportFF();
};
