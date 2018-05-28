#pragma once
#include "Oferta.h"
#include "repo.h"
#include <string>
#include<Controller.h>
class ActiuneUndo {
public:
	virtual std::string doUndo() = 0;

	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Oferta ofertaAdaugata;
	Repo& repo;
public:
	UndoAdauga(Repo& rep, const  Oferta& p) :repo{ rep }, ofertaAdaugata{ p } {}
	std::string doUndo() override {
		repo.delt3(ofertaAdaugata);
		
		return ofertaAdaugata.getName();

	}
};

class UndoSterge : public ActiuneUndo {
	Oferta ofertaStearsa;
	Repo& repo;
public:
	UndoSterge(Repo& rep, const  Oferta& p) :repo{ rep }, ofertaStearsa{ p } {}
	std::string doUndo() override {
		repo.store(ofertaStearsa);
		return ofertaStearsa.getName();

	}
};

class UndoChange : public ActiuneUndo {
	Oferta ofertaChanged;
	Repo& repo;
public:
	UndoChange(Repo& rep, const  Oferta& p) :repo{ rep }, ofertaChanged{ p } {}
	std::string doUndo() override {
		repo.change(ofertaChanged);
		return ofertaChanged.getName();
	}
};