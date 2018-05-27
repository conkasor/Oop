#pragma once
#include <string>

#include <vector>
#include "Oferta.h"
using namespace std;

class ValidateException {
public:
	string msg;
	ValidateException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);
class ValidatorOferte
{	
public:

	void validate(const Oferta& of);



};

