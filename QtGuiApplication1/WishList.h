#pragma once
#include <vector>
#include "Oferta.h"
#include "repo.h"
#include "Observer.h"
class WishList:public Observable{
private:
	std::vector<Oferta> wishList;
public:
	WishList()noexcept {};

	void EmptyWishList();

	void AddToWishList(const Oferta & of);

	void DeleteWishListOffer(const Oferta & of);

	void ChangeWishListOffer(const Oferta & of);

	void AddWishListOffer(std::vector<Oferta> filtrat);

	void RandomAddWishList(std::vector<Oferta> all, const unsigned int nr);

	void getAll(std::vector<Oferta>& v);
	void addObserver(Observer* obs);
	int size()noexcept;
};

