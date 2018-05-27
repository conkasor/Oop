#pragma once
#include "Oferta.h"
#include <vector>
using namespace std;

class Repo {
	std::vector<Oferta> repo;

public:
	void store(const Oferta& p);
	bool find(const Oferta& name)noexcept;
	void delt3(const Oferta& name);
	void change(const Oferta of2);
	Oferta get(const Oferta& of);
	Oferta getEl(const int poz)const;
	void afisare();
	int size()noexcept;
	void getAll(std::vector<Oferta>& rez)const;
	
};

class RepoException {
public:
	string msg;
	RepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);

void testRepo();
	

