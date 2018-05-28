#include "controller.h"
#include <assert.h>
#include <algorithm>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <iostream>
#include <memory>
#include "Oferta.h"
#include "undo.h"
#include "Observer.h"
using namespace std;
//adaugam nou obiect in repo la nivel controller daca sunt validate
void Controller::add(const string & name, const string & dest, const string & tipe, int price)
{
	Oferta of(name, price, dest, tipe);
	val.validate(of);
	repo.store(of);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, of));
	notifyObservers(name);
}

std::string Controller::undo() {
	if (undoActions.empty()) {
		throw CtrlException{ "Nu mai exista operatii" };
	}
	
	std::string st=undoActions.back()->doUndo();
	undoActions.pop_back();
	notifyObservers(st);
	return st;
}


//sterge element dat prin intermediul numelui din repo la nivel controller
void Controller::del(const string & name)
{
	Oferta of(name);
	repo.delt3(of);
	
	try{ 
		while (1)
			wishList.DeleteWishListOffer(of);

	}
	catch (CtrlException) {}
	undoActions.push_back(std::make_unique<UndoSterge>(repo, of));
	notifyObservers(name);

}
//modifica elementul din wishlist si repo la nivel controller
void Controller::change(const string & name,const string & dest,const string & tipe,const int price)
{
	Oferta of(name, price, dest, tipe);
	Oferta ofv;
	ofv = repo.get(of);
	val.validate(of);
	repo.change(of);
	
	try {
		wishList.ChangeWishListOffer(of);

	}
	catch (CtrlException){}
	undoActions.push_back(std::make_unique<UndoChange>(repo, ofv));
	notifyObservers(name);

}

//filtreaza destinatie 
void Controller::filtrareDest(const string & dest, std::vector<Oferta>& rez)const
{
	filter([dest](const Oferta& of) noexcept {
		return of.getDestination() == dest;
	},rez);
}
//filtrare generica
void Controller::filter(function<bool(const Oferta&)> fct, std::vector<Oferta>& rez) const
{
	std::vector<Oferta> rezz;
	repo.getAll(rezz);
	copy_if(rezz.begin(), rezz.end(), back_inserter(rez), fct);
}

//filtrare dupa Pet
void Controller::filtrarePret(const int pret,std::vector<Oferta>& rez) const
{
	filter([pret](const Oferta& of) noexcept {
		return of.getPrice() <= pret;
	}, rez);
}
//functie generala de sortare 
void Controller::sorting(function<bool(const Oferta&,const Oferta&)> fct, std::vector<Oferta>& rez)
{
	repo.getAll(rez);
	sort(rez.begin(),rez.end(),fct);
	
}
//sorteaza dupa nume
void Controller::sortNume(std::vector<Oferta>& rez)
{
	sorting([](const Oferta& of, const Oferta& of1) noexcept {
		return of.getName() < of1.getName();
	}, rez);
}
//sortare dupa destinatie
void Controller::sortDest(std::vector<Oferta>& rez)
{
	sorting([](const Oferta& of, const Oferta& of1) noexcept {
		return of.getDestination() < of1.getDestination();
	}, rez);
}
//sortare dupa tip
void Controller::sortTipPret(std::vector<Oferta>& rez)
{
	sorting([](const Oferta& of, const Oferta& of1) noexcept {
		if (of.getType() < of1.getType())
			return 1;
		else if (of.getType() == of1.getType())
			if (of.getPrice() < of1.getPrice())
				return 1;
		return 0;
	}, rez);
}
//returneaza prin paramatru lista cu toate obiectele din repo
void Controller::getAll(std::vector<Oferta>& rez)const
{
	repo.getAll(rez);
}
//returneaza un element dupa nume
Oferta Controller::get(const string &name)const
{
	Oferta of(name);
	if (repo.find(of))
		return repo.get(of);
	throw CtrlException("Nu exista aceasta oferta");
}
//Returneaza dimensiunea repositoryului
int Controller::size()const noexcept{
	return repo.size();
}

void Controller::addWishObserver(Observer* obs)
{
	wishList.addObserver(obs);
}

void Controller::addObserverr(Observer * obs)
{
	addObserver(obs);
}









ostream& operator<<(ostream& out, const CtrlException& ex) {
	out << ex.msg;
	return out;
}



void testController() {
	Repo rep;
	WishList wishList;
	ValidatorOferte val;
	Controller ctr{ rep,val,wishList };
	ctr.add("Dicky4", "aicky Island", "Dicking around", 9001);
	ctr.add("Dicky1", "bicky Island", "Dicking around", 9000);
	ctr.add("Dicky2", "aicky Island", "Dicking arouna", 9003);
	{std::vector<Oferta> rez;

	ctr.filtrareDest("Dicky Island", rez);
	//assert(rez.size() == 2);
	}
	std::vector<Oferta> rez;

	ctr.filtrarePret(9001, rez);
	assert(rez.size() == 1);
	std::vector<Oferta> rez1;
	ctr.sortNume(rez1);
	std::vector<Oferta> rez2;
	ctr.sortDest(rez2);
	std::vector<Oferta> rez3;
	ctr.sortTipPret(rez3);
	string name = "Dicky4";
	string d = "fkfk";
	string t = "dkkf";
	ctr.get("Dicky4");
	ctr.change(name, d,t, 20);
	ctr.del(name);
	ctr.undo();
	std::vector <Oferta> rez4;
	ctr.getAll(rez4);
}
