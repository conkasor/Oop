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
#include "controller.h"
#include "wishList.h"
#include "qslider.h"
#include "Observer.h"
#include "Model.h"

class ClientMenu : public QWidget, public Observer, public Observable
{
	Controller& ctrl;
	QWidget* wstatus = new QWidget();
	QWidget* client = new QWidget();
	QWidget* wfrow = new QWidget();
	QWidget* wsrow = new QWidget();
	QWidget* wbtns = new QWidget();
	QWidget* wtrow = new QWidget();
	QHBoxLayout* status = new QHBoxLayout(wstatus);
	QHBoxLayout *frow = new QHBoxLayout(wfrow);
	QHBoxLayout *srow = new QHBoxLayout(wsrow);
	QVBoxLayout *all = new QVBoxLayout(client);
	QVBoxLayout *btns = new QVBoxLayout(wbtns);
	QListWidget *l1 = new QListWidget(wfrow);
	QListWidget *l2 = new QListWidget(wfrow);
	QHBoxLayout* trow = new QHBoxLayout(wtrow);

public:
	ClientMenu(Controller& ctrl) :ctrl{ ctrl } {};
	QPushButton * wantB = new QPushButton("<<Want", wbtns);
	QLabel* currentNrLabel = new QLabel("0", wbtns);
	QPushButton *dWantB = new QPushButton(">>Don't want", wbtns);
	QSlider* slider = new QSlider(wtrow);
	QLabel* statusLabel = new QLabel(client);
	QPushButton *delAll = new QPushButton("DelAll", wsrow);
	QPushButton *generateB = new QPushButton("Generate 1", wsrow);
	QPushButton *exportToHtml = new QPushButton("Export Html", wsrow);

	void exit();
	void exec();
	void connects();
	void populateFromVector(QListWidget * l, std::vector<Oferta>& v);
	void add(Oferta & of, QListWidget * l1);
	void generate();
	void deleteAll();
	void exportHtml();
	void update(std::string name = "") override;
	void notifyViewOnly(std::string name = "");
};
