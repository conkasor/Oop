#include "ViewWishList.h"

void ViewWishList::update(std::string name)
{
	rands r;
	auto s = wishList.size();
	std::vector<Oferta> vect;
	wishList.getAll(vect);
	if (s > v.size())
		for (int i = v.size(); i < s; i++) {
			r.name = name;
			r.x = 1 + (int)(400.0* (rand() / (RAND_MAX + 1.0)));
			r.y = 1 + (int)(400.0 * (rand() / (RAND_MAX + 1.0)));
			r.z = vect[i].getPrice() / 10;
			r.a = vect[i].getPrice() / 10;
			r.b = 1 + (int)(9.0 * (rand() / (RAND_MAX + 1.0)));
			v.push_back(r);
		}
	else if (s == 0) {
		v.clear();
	}
	else if (v.size() > s && s != 0) {
		for (int i = 0; i < v.size(); i++) {
			if (v[i].name == name)
			{
				v.erase(v.begin() + i);
				break;
			}
		}
	}
	repaint();
}

void ViewWishList::exec() {
	this->update();
	this->show();
}