#pragma once
#include "Oferta.h"
#include "repo.h"
#include "ValidatorOferte.h"
#include <functional>
#include <vector>
#include <string>
#include "undo.h"
#include <memory>
#include "WishList.h"
#include "Observer.h"
using namespace std;
class Controller:public Observable
{
	Repo& repo;
	ValidatorOferte& val;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
	
public:
	
	WishList & wishList;
	Controller(Repo& rep, ValidatorOferte& val, WishList& wishList) noexcept : repo{ rep }, val{ val }, wishList{ wishList } {
	}
	
	void add(const string & name, const string & dest, const string & tipe, int price);
	std::string undo();
	void del(const string& name);
	void change(const string& name,const string& dest,const string& tipe,const int price);
	void print() {
		repo.afisare();
	}
	void filtrareDest(const string& dest, std::vector<Oferta>& rez)const;
	void filter(function<bool(const Oferta&)> fct, std::vector<Oferta>& rez)const;
	void filtrarePret(const int pret, std::vector<Oferta>& rez)const;
	void sorting(function<bool(const Oferta&, const Oferta&)> fct, std::vector<Oferta>& rez);
	void sortNume(std::vector<Oferta>& rez);
	void sortDest(std::vector<Oferta>& rez);
	void sortTipPret(std::vector<Oferta>& rez);
	void getAll(std::vector<Oferta>&rez)const;
	Oferta get(const string& name)const;
	int size()const noexcept;
	void addWishObserver(Observer* obs);
	void addObserverr(Observer* obs);



};
class CtrlException {
public:
	string msg;

	CtrlException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const CtrlException& ex);
};

ostream& operator<<(ostream& out, const CtrlException& ex);

void testController();

