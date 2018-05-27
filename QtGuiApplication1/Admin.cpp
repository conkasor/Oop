#include "Admin.h"
#include "qstring.h"
#include <string>
#include <qdebug.h>
#include <qcolor.h>
#include <qdesktopservices.h>
#include <qurl.h>
#include <fstream>
#include <qtoolbar.h>
#include <qstatusbar.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qstyle.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qshortcut.h>
#include <qkeysequence.h>
#include <qsound.h>

void Admin::exec()
{
	
	//general menu
	menu->addWidget(statusBar);
	menu->addWidget(l1);
	buttons->addWidget(sortCB);
	
	filterForm->addWidget(filterCB);
	
	filterForm->addWidget(filterEdit);
	buttons->addWidget(wFilterForm);
	buttons->addWidget(undoB);
	impExp->addWidget(importB);
	impExp->addWidget(exportB);
	fileLabel->setText("File for export/import:");
	fileEdit->setText("impExp.txt");
	formFile->addWidget(fileLabel);
	formFile->addWidget(fileEdit);
	impExp->addWidget(wFileForm);
	buttons->addWidget(exportHtmlB);	menu->addWidget(wButtons); menu->addWidget(wImpExp); menu->addWidget(wImpExp);
	frow->addWidget(wMenu);


	
	// formurile
	modifyForm->addRow(lName, eName);
	modifyForm->addRow(lDest, eDest);
	modifyForm->addRow(lType, eType);
	modifyForm->addRow(lPrice, ePrice);
	modifyMenuT->addStretch();
	modifyMenuT->addWidget(imgLabel);
	myImage->load("gabi.png");
	imgLabel->setPixmap(*myImage);
	imgLabel->setVisible(false);
	modifyMenuT->addWidget(wModifyForm);
	modifyButtons->addWidget(addB);
	modifyButtons->addWidget(deleteB);
	modifyButtons->addWidget(changeB);
	modifyButtons->addWidget(getB);
	modifyMenuT->addWidget(wModifyButtons);
	frow->addWidget(wModifyMenu);
	
	//
	statusBar->setSizeGripEnabled(false);
	sound->setMedia(QUrl::fromLocalFile("ameno.mp3"));
	sound->audioRole();
	connects();
	
	all->show();

}


void Admin::connects()
{
		connect(addB, &QPushButton::clicked, [this]() {add(); });
		connect(deleteB, &QPushButton::clicked, [this]() {del(); });
		connect(changeB, &QPushButton::clicked, [this]() {change(); });
		connect(l1, &QListWidget::itemSelectionChanged, [this]() {get(l1->currentItem()->text().toStdString()); });
		connect(getB, &QPushButton::clicked, [this]() {get(eName->text().toStdString()); });
		connect(sortCB, QOverload<int>::of(&QComboBox::activated), [=](int index) {switch (index)
		{
		case 1: sortByName(); sortCB->setCurrentIndex(0); break;
		case 2: sortByDest(); sortCB->setCurrentIndex(0); break;
		case 3: sortTypePrice(); sortCB->setCurrentIndex(0); break;
			default:break;


		}});
		connect(filterCB, QOverload<int>::of(&QComboBox::activated), [=](int index) {switch (index)
		{
		case 1: filterByPrice(); filterCB->setCurrentIndex(0); break;
		case 2: filterByDest(); filterCB->setCurrentIndex(0); break;
		case 3: populateAll(); filterCB->setCurrentIndex(0); break;
		default:break;


		}});
		connect(undoB, &QPushButton::clicked, [this]() {doUndo(); });
		connect(exportHtmlB, &QPushButton::clicked, [this]() {toHtml(); QString link = "out.html";
		QDesktopServices::openUrl(QUrl(link)); });
		connect(importB, &QPushButton::clicked, [this]() {importFF(); });
		connect(exportB, &QPushButton::clicked, [this]() {exportFF(); });
		connect(shortcut, &QShortcut::activated, [this]() {  imgLabel->setVisible(true); sound->play(); });
		connect(shortcut1, &QShortcut::activated, [this]() {imgLabel->setVisible(false); sound->pause(); });
}


void Admin::populateFromVector(QListWidget& l,std::vector<Oferta>& v)
{
	for (auto& el : v) {
		std::string name = el.getName();
		l.addItem(QString::fromStdString(name));	
	}
}



void Admin::add()
{

	std::string name = eName->text().toStdString();
	int iprice;
	std::string dest = eDest->text().toStdString();
	std::string type= eType->text().toStdString();
	std::string price= ePrice->text().toStdString();
	try {
		iprice = std::stoi(price);
		ctrl.add(name, dest, type, iprice);
		l1->clear();
		populateAll();
		statusBar->showMessage("Offer added!");
	}
	catch (RepoException& e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
	catch (ValidateException&e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
	catch (CtrlException&e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
	catch (exception) { statusBar->showMessage("Invalid Price!"); };


}
void Admin::del() {
	try {
		std::string name = eName->text().toStdString();
		qDebug() << eName->text();
		ctrl.del(name);
		l1->clear();
		std::vector<Oferta> v;
		ctrl.getAll(v);
		populateFromVector(*l1, v);

		statusBar->showMessage("Offer deleted!");

	}
	catch (RepoException& e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
	catch (ValidateException&e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
	catch (CtrlException&e) { statusBar->showMessage(QString::fromStdString(e.msg)); };

}
void Admin::get(std::string name) {
	try {
		Oferta of = ctrl.get(name);
		eName->setText(QString::fromStdString(of.getName()));
		eDest->setText(QString::fromStdString(of.getDestination()));
		eType->setText(QString::fromStdString(of.getType()));
		ePrice->setText(QString::fromStdString(std::to_string(of.getPrice())));
		statusBar->showMessage("Offer found!");
	}
	catch (RepoException& e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
	catch (ValidateException&e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
	catch (CtrlException&e) { statusBar->showMessage(QString::fromStdString(e.msg)); };

}
void Admin::sortByName() {
	std::vector<Oferta> v;
	ctrl.sortNume(v);
	l1->clear();
	populateFromVector(*l1, v);
	statusBar->showMessage("Sorted!");
}
void Admin::sortByDest() {
	std::vector<Oferta> v;
	ctrl.sortDest(v);
	l1->clear();
	populateFromVector(*l1, v);
	statusBar->showMessage("Sorted!");
}
void Admin::sortTypePrice() {
	std::vector<Oferta> v;
	ctrl.sortTipPret(v);
	l1->clear();
	populateFromVector(*l1, v);
	statusBar->showMessage("Sorted!");
}
void Admin::notify()
{
}
void Admin::filterByDest() {
	std::vector<Oferta> v;
	std::string dest = filterEdit->text().toStdString();
	ctrl.filtrareDest(dest, v);
	populateFromVector(*l1, v);
	l1->clear();
	populateFromVector(*l1, v);
	if (v.size()==0)
		statusBar->showMessage("No Offers that have this destination!");
	else
	statusBar->showMessage("Filtered!");
	filterEdit->setText("");

}
void Admin::filterByPrice() {
	std::vector<Oferta> v;
	std::string price = filterEdit->text().toStdString();
	int iprice;
	try {
		iprice = stoi(price);
		
		ctrl.filtrarePret(iprice, v);
		l1->clear();
		populateFromVector(*l1, v);
		if (v.size() == 0)
			statusBar->showMessage("No Offers that have this destination!");
		else
			statusBar->showMessage("Filtered!");
	}
		catch (exception) { statusBar->showMessage("You need a number to filter by Price!"); };
		filterEdit->setText("");

}
void Admin::populateAll() {
	std::vector<Oferta> v;
	ctrl.getAll(v);
	l1->clear();
	populateFromVector(*l1, v);

}
void Admin::doUndo() {
	try {
		std::string st = ctrl.undo();
		l1->clear();
		populateAll();
		if (!l1->findItems(QString::fromStdString(st), Qt::MatchCaseSensitive).isEmpty())
			l1->findItems(QString::fromStdString(st), Qt::MatchCaseSensitive).at(0)->setBackgroundColor(200);
		statusBar->showMessage("Undo executed succesfully!");
	}
	catch (RepoException& e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
	catch (ValidateException&e) { statusBar->showMessage(QString::fromStdString(e.msg)); }
	catch (CtrlException&e) { statusBar->showMessage(QString::fromStdString(e.msg)); };
}
void Admin::toHtml() {
	std::vector<Oferta> v;
	ctrl.getAll(v);
	ofstream g("out.html");
	g<<"<!DOCTYPE HTML><html><table style = 'width:100%'><tr>";
	g << "<th>Offer's name</th>";
	g << "<th>Destination</th>";
	g << "<th>Type</th>";
	g << "<th>Price</th>";
	for (auto& el : v) {
		g<<"<tr>";
		g << "<td>" << el.getName() << "</td>";
		g << "<td>" << el.getDestination() << "</td>";
		g << "<td>" << el.getType() << "</td>";
		g << "<td>" << el.getPrice() << "</td>";
		g << "</tr>";
	}
	g << "</table>";
	statusBar->showMessage("Html export executed succesfully!");
}
void Admin::importFF() {
	ifstream f("impExp.txt");
	std::string name, dest, typ,price;
	int iprice;
		while (std::getline(f,name) , std::getline(f,dest), std::getline(f,typ), std::getline(f,price)) {
			iprice = std::stoi(price);
			ctrl.add(name, dest, typ, iprice);

		}
	populateAll();
		statusBar->showMessage("Import executed succesfully!");
}
void Admin::exportFF() {
	ofstream g("impExp.txt");
	std::vector<Oferta> v;
	ctrl.getAll(v);
	for (auto& el : v) {
		g << el.getName() << endl;
		g << el.getDestination() << endl;
		g << el.getType() << endl;
		g << el.getPrice() << endl;
	}
	statusBar->showMessage("Export executed succesfully!");
}
