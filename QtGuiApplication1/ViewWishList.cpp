#include "ViewWishList.h"

void ViewWishList::update()
{
	srand(time(0));
	rands r;
	auto s = wishList.size();
	std::vector<Oferta> vect;
	wishList.getAll(vect);
	if (s > v.size())
	for (int i=v.size(); i <s; i++) {
		r.x = rand() % 450;
		r.y = rand() % 450;
		r.z = vect[i].getPrice() / 10;
		r.a = vect[i].getPrice() / 10;
		r.b = rand() % 10;
		v.push_back(r);
	}
	else while (v.size() > s) {
		v.pop_back();
	}
	repaint();
}

void ViewWishList::exec(){
	this->update();
	this->show();

}
