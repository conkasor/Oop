#pragma once
#include "Oferta.h"
#include "repo.h"
#include <string>
class ActiuneUndo {
public:
	virtual std::string doUndo() = 0;

	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Oferta ofertaAdaugata;
	Repo& rep;
public:
	UndoAdauga(Repo& rep, const  Oferta& p) :rep{ rep }, ofertaAdaugata{ p } {}
	std::string doUndo() override {
		rep.delt3(ofertaAdaugata);
		return ofertaAdaugata.getName();

	}
};

class UndoSterge : public ActiuneUndo {
	Oferta ofertaStearsa;
	Repo& rep;
public:
	UndoSterge(Repo& rep, const  Oferta& p) :rep{ rep }, ofertaStearsa{ p } {}
	std::string doUndo() override {
		rep.store(ofertaStearsa);
		return ofertaStearsa.getName();

	}
};

class UndoChange : public ActiuneUndo {
	Oferta ofertaChanged;
	Repo& rep;
public:
	UndoChange(Repo& rep, const  Oferta& p) :rep{ rep }, ofertaChanged{ p } {}
	std::string doUndo() override {
		rep.change(ofertaChanged);
		return ofertaChanged.getName();
	}
};