#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Oferta.h"
#include <vector>

using namespace std;
bool Oferta::operator==(const Oferta& oth)const noexcept {
	return  this->name == oth.getName();
}