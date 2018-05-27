#include "ValidatorOferte.h"
#include <vector>

using namespace std;
ostream& operator<<(ostream& out, const ValidateException& ex) {
	out << ex.msg;
	return out;
}

void ValidatorOferte::validate(const Oferta & of)
{
	string msgs;
	if (of.getName().empty())
{
		msgs =msgs+ "Nume vid!\n";
}

if (of.getPrice()<0)
{  
	msgs=msgs+"Pret INVALID!, trebuie sa fie int >0\n";
}
if (of.getDestination().empty()) {
	msgs=msgs+"Destinatie vida!\n";
}
if (of.getType().empty()) {
	msgs=msgs+"Type vid!\n";
}
if (msgs!="") {
	throw ValidateException(msgs);
}
}
