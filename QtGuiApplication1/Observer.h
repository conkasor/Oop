#pragma once
#include <vector>
#include <string>
class Observer
{
public:
	virtual void update(std::string name="") = 0;
};



class Observable {
protected:
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}
	void notifyObservers(std::string name="") {
		for (auto *obs: observers) {
			obs->update(name);
		}
	}
};

