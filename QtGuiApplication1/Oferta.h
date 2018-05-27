#pragma once
#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include<istream>
using namespace std;
class Oferta {
private:
	string name;
	int price;
	string destination;
	string tip;

public:
	
	Oferta(const string Cname, int Cprice, const string Cdest, const string Ctip) :name{ Cname }, price{ Cprice }, destination{ Cdest }, tip{ Ctip }{}
	Oferta()noexcept :name{ "None" }, price{ 0 }, destination{ "None" }, tip{ "None" } {};
	Oferta(const string Cname) :name{ Cname }, price{ 0 }, destination{ "None" }, tip{ "None" } {};
	int getPrice()const noexcept{
		return price;
	}
	string getName()const noexcept {
		return name;
	}
	string getType() const noexcept {
		return tip;
	}
	string getDestination() const noexcept {
		return destination;
	}
	void setPrice(const int newPrice)noexcept {
		price = newPrice;
	}
	void setType(const string newType) {
		tip = newType;
	}
	void setDestination(const string newDestination) {
		destination = newDestination;
	}
	bool operator==(const Oferta& oth)const noexcept;
	
	static void testeDomain() {
		string n = "name";
		string d = "Peste tot";
		string t = "relaxare";
		const int p = 200;
		Oferta of1(n, p, d, t);
		Oferta of2(n, p, d, t);
		assert(of1 == of2);


	}
	friend ostream &operator<<(ostream &output, const Oferta &of) {
		output <<of.getName() << "/" << of.getPrice() << "/" << of.getDestination() << "/" << of.getType() << endl;
		return output;
	}
};

