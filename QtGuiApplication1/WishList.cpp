#include "WishList.h"
#include <vector>
#include "repo.h"
#include "Controller.h"
#include <random>

//Goleste wishlistul
void WishList::EmptyWishList() {
	for (auto& of : wishList) {
		std::vector<string> v;
		auto temp = wishList.erase(wishList.begin());
		v.push_back(of.getName());

		
	}
	notifyObservers();
	
}
//Adauga la wishList oferta primita ca parametru
void WishList::AddToWishList(const Oferta& of) {
	try { wishList.emplace_back(of); notifyObservers(of.getName()); }
	catch (RepoException& ex) {
		cout << ex;
	}
}
//sterge oferta data ca parametru din wishlist
void WishList::DeleteWishListOffer(const Oferta& of) {
	std::vector<Oferta>::iterator it;
	it = find(wishList.begin(), wishList.end(), of);
	if (it != wishList.end())
	{
		auto temp = wishList.erase(it);
		notifyObservers(of.getName());
		return;
	}
	throw CtrlException("Nu exista aceasta oferta pentru a fi stearsa");
}

//Modifica elementul cu aceeasi denumire ca cel dat ca parametru din wishlist
void WishList::ChangeWishListOffer(const Oferta& of) {
	std::vector<Oferta>::iterator it;
	it = find(wishList.begin(), wishList.end(), of);
	if (it != wishList.end())
	{
		auto temp = wishList.erase(it);
		AddToWishList(of);
		notifyObservers();
		return;
	}
	throw CtrlException("Nu exista aceasta oferta, deci nu se poate modifica");
}
//Adauga TOATE elementele care au aceeasi destinatie cu destinatia primita ca parametru
void WishList::AddWishListOffer(std::vector<Oferta> filtrat) {
	
	for (auto of : filtrat) {
		wishList.emplace_back(of);
		notifyObservers(of.getName());
	}
	
}
//Populeaza Wishlistul cu un nr. dat ca parametru de oferte random din repo;
void WishList::RandomAddWishList(std::vector<Oferta> all,const unsigned int nr) {
	std::mt19937 mt{ std::random_device{}() };
	if (all.size() == 0)
		throw CtrlException("Nu aveti nici o Oferta, va rog introduceti macar o oferta");
	const std::uniform_int_distribution<> dist(0, all.size() - 1);
	if (nr > all.size())
		throw CtrlException("Nr. de elemente cerut e mai mare decat numarul total");
	for (unsigned int i = 0; i < nr; i++) {
		const int rndNr = dist(mt);
		auto el = all[rndNr];
		wishList.push_back(el);
		notifyObservers(el.getName());
	}
	
}

void WishList::getAll(std::vector<Oferta>& v) {
	for (auto& el : wishList)
		v.emplace_back(el);
}
void WishList::addObserver(Observer * obs)
{
	Observable::addObserver(obs);

}
int WishList::size()noexcept {
	return wishList.size();
}