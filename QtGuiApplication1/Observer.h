#pragma once
#include <vector>
class Observer
{
public:
	virtual void update() = 0;
};



class Observable {
	std::vector<Observer*> observers;
public:
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}
	void notifyObservers() {
		for (auto *obs: observers) {
			obs->update();
		}
	}
};

