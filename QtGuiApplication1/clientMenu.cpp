#include "clientMenu.h"
#include "wishList.h"
#include <qdebug.h>
#include <fstream>
#include "Controller.h"
#include "qurl.h"
#include <qdesktopservices.h>
#include "ViewWishList.h"
#include "Model.h"
void ClientMenu::exit()
{
}

void ClientMenu::exec()
{
	btns->addWidget(wantB);
	btns->addWidget(currentNrLabel);
	btns->addWidget(dWantB);

	frow->addWidget(l1);
	frow->addWidget(wbtns);
	frow->addWidget(l2);

	srow->addWidget(delAll);
	srow->addWidget(generateB);
	srow->addWidget(exportToHtml);
	trow->insertStretch(0, 0);
	trow->addWidget(slider);
	trow->insertStretch(2, 0);
	slider->setOrientation(Qt::Horizontal);
	slider->setRange(1, ctrl.size());
	qDebug() << ctrl.size();

	status->addWidget(statusLabel);
	all->addWidget(wstatus);
	all->addWidget(wfrow);
	all->addWidget(wsrow);
	all->addWidget(wtrow);
	connects();
	//populate all
	std::vector<Oferta> v;
	ctrl.getAll(v);
	populateFromVector(l2, v);
	client->show();
}

void ClientMenu::connects()
{
	connect(slider, &QSlider::valueChanged, [this]() {
		QString str = "Generate ";

		str += QString::number(slider->value());
		generateB->setText(str); });

	connect(l2, &QListWidget::doubleClicked, [this]() {
		Oferta& of = ctrl.get(l2->currentItem()->text().toStdString());
		add(of, l1);
		ctrl.wishList.AddToWishList(of);
		update(of.getName());
		notifyObservers(of.getName());
	});
	connect(wantB, &QPushButton::clicked, [this]() {
		try {
			if (!l2->currentItem())
				throw(CtrlException("Nu ati selectat oferta pe care sa o adaugati in wishlist"));
			Oferta& of = ctrl.get(l2->currentItem()->text().toStdString());
			add(of, l1);
			ctrl.wishList.AddToWishList(of);
			update(of.getName());
			notifyObservers(of.getName());
		}
		catch (CtrlException& e) {
			statusLabel->setText(QString::fromStdString(e.msg));
		};
	});
	connect(dWantB, &QPushButton::clicked, [this]() {
		try {
			if (!l1->currentItem())
				throw(CtrlException("Nu ati selectat Offer wishlist"));
			Oferta& of = ctrl.get(l1->currentItem()->text().toStdString());
			ctrl.wishList.DeleteWishListOffer(of);
			l1->clear();
			std::vector<Oferta> v;
			ctrl.wishList.getAll(v);
			populateFromVector(l1, v);
			update(of.getName());
			notifyObservers(of.getName());
		}
		catch (CtrlException& e) {
			statusLabel->setText(QString::fromStdString(e.msg));
		}
		catch (exception) {};
	});
	connect(l1, &QListWidget::doubleClicked, [this]() {
		try {
			Oferta& of = ctrl.get(l1->currentItem()->text().toStdString());
			ctrl.wishList.DeleteWishListOffer(of);
			std::vector<Oferta> v;
			ctrl.wishList.getAll(v);
			update(of.getName());
			notifyObservers(of.getName());
		}
		catch (CtrlException& e) {
			statusLabel->setText(QString::fromStdString(e.msg));
		}
		catch (exception) {};
	});
	connect(generateB, &QPushButton::clicked, [this]() {
		generate();
		currentNrLabel->setText(QString::number(ctrl.wishList.size()));
		update();
	});
	connect(delAll, &QPushButton::clicked, [this]() {
		if (ctrl.wishList.size() == 0)
			statusLabel->setText("Deja Gol");
		else {
			deleteAll();
			notifyObservers();
		}});
	connect(exportToHtml, &QPushButton::clicked, [this]() {exportHtml(); QString link = "outwish.html";
	QDesktopServices::openUrl(QUrl(link)); });
}

void ClientMenu::populateFromVector(QListWidget* l, std::vector<Oferta>& v)
{
	l->clear();
	for (auto& el : v) {
		add(el, l);
	}
}
void ClientMenu::add(Oferta& of, QListWidget* l1) {
	QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(of.getName()));
	QString dest = QString::fromStdString(of.getDestination());
	QString type = QString::fromStdString(of.getType());
	QString price = QString::number(of.getPrice());
	dest += ", " + type + ", " + price;
	item->setToolTip(dest);
	l1->addItem(item);
}
void ClientMenu::generate() {
	std::vector<Oferta> v;
	ctrl.getAll(v);
	ctrl.wishList.RandomAddWishList(v, slider->value());
	update();
}
void ClientMenu::deleteAll() {
	l1->clear();
	ctrl.wishList.EmptyWishList();
	update();
}

void ClientMenu::exportHtml()
{
	std::vector<Oferta> v;
	ctrl.wishList.getAll(v);
	ofstream g("outwish.html");
	g << "<!DOCTYPE HTML><html><table style = 'width:100%'><tr>";
	g << "<th>Offer's name</th>";
	g << "<th>Destination</th>";
	g << "<th>Type</th>";
	g << "<th>Price</th>";
	for (auto& el : v) {
		g << "<tr>";
		g << "<td>" << el.getName() << "</td>";
		g << "<td>" << el.getDestination() << "</td>";
		g << "<td>" << el.getType() << "</td>";
		g << "<td>" << el.getPrice() << "</td>";
		g << "</tr>";
	}
	g << "</table>";
	statusLabel->setText("Html export executed succesfully!");
}

void ClientMenu::update(std::string name)
{
	std::vector<Oferta> v;
	ctrl.wishList.getAll(v);
	populateFromVector(l1, v);
	v.clear();
	ctrl.getAll(v);
	populateFromVector(l2, v);
	currentNrLabel->setText(QString::number(ctrl.wishList.size()));
	slider->setRange(1, ctrl.size());
	notifyViewOnly(name);
}

void ClientMenu::notifyViewOnly(std::string name)
{
	for (auto el : observers) {
		if (typeid(this) != typeid(el))
			el->update(name);
	}
}