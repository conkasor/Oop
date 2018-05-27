#include "repo.h"
#include <assert.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

//adauga element in repo
void Repo::store(const Oferta& of) {
	if (find(of))
		throw RepoException("Exista deja oferta asta ");
	else {repo.emplace_back(of);
	}

}
//cauta element in repo
bool Repo::find(const Oferta& name)noexcept
{
	for (const Oferta& of : repo)
		if (of == name)
			return true;
	return false;

}
//sterge element din repo
void Repo::delt3(const Oferta& of)
{
	if (!find(of))
		throw RepoException("Nu exista elementu deci nu se poate sterge");
	std::vector<Oferta>::iterator it;
	it = std::find(repo.begin(), repo.end(), of);
	if (it != repo.end())
	{
		auto temp = repo.erase(it);
		return;
	}

		
}
//modifica element in repo
void Repo::change(const Oferta of2)
{
	if (find(of2))
	{
		delt3(of2);
		repo.push_back(of2);
	}
	else 
		throw RepoException("Nu exista elementu deci nu se poate modifica");
}
//returneaza obiect dat ca parametru din repo
Oferta Repo::get(const Oferta& of)
{
	for (Oferta off : repo)
		if (of == off)
			return off;
	return of;
}
//returneaza al n-lea element din lista la nivel de repo

Oferta Repo::getEl(const int poz) const
{
	return repo[poz];
}
//afiseaza toate elementele din lista la nivel de repo
void Repo::afisare()
{
	for (const Oferta& of : repo)
		cout << of;

}
//returneaza nr de obiecte din repo
int Repo::size()noexcept
{	
	return repo.size();
}
//returneaza lista cu toate elementele din repo
void Repo::getAll(std::vector<Oferta>& rez)const
{
	for (auto el : repo)
		rez.push_back(el);
}

ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.msg;
	return out;
}

void testRepo() {
	Repo r;
	Oferta of("2", 2, "3", "4");
	Oferta of1("3", 2, "3", "4");
	r.store(of);
	assert(r.find(of) == 1);
	r.store(of1);
	assert(r.size() == 2);
	assert(r.find(of1) == 1);
	r.delt3(of);
	assert(r.size() == 1);
	r.store(of);
	of.setDestination("panamera");
	r.change(of);
	r.getEl(1);
	assert(r.get(of).getDestination() == "panamera");
	try {
		r.store(of);
		assert(false);}
	catch (RepoException&) {
		assert(true);
	}
	r.delt3(of1);
	try {
		r.delt3(of1);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		r.change(of1);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

}