#pragma once
#include "Oferta.h"
#include <vector>
#include <Observer.h>
#include <qpainter.h>
#include <qpaintengine.h>
#include <qpaintdevicewindow.h>
#include <qwidget.h>
#include <WishList.h>
#include <time.h>
#include <qwidget.h>
#include <QPaintEvent>
#include <qcolor.h>

class ViewWishList:public Observer,public QWidget
{
	WishList& wishList;
	typedef struct rands {
		int x;
		int y;
		int z;
		int a;
		int b;
	};
	std::vector<QColor>colors{ Qt::gray,Qt::red,Qt::cyan,Qt::black,Qt::blue,Qt::darkMagenta,Qt::darkYellow,Qt::yellow,Qt::white,Qt::darkRed};
	std::vector<rands> v;
public:
	QRegion * region = new QRegion(0,0,1000,1000);
	QPaintEvent* e = new QPaintEvent(*region);
	ViewWishList(WishList& w) :wishList{ w } {};
	void paintEvent(QPaintEvent*) {
		QPainter painter(this);
		for(int i=0;i<v.size();i++)
			painter.fillRect(v[i].x,v[i].y,v[i].z, v[i].a, colors[v[i].b]);
	}
	void update() override;
	void exec();
};

