#include "GameObservers.h"
#include <list>
#include <iostream>

using namespace std;


//Subject class implementation
Subject::Subject()
{
	observers = new list<Observer*>;
}

Subject::~Subject()
{
	delete observers;
}

void Subject::attach(Observer* observer) {
	observers->emplace_back(observer);
}

void Subject::detach(Observer* observer_to_delete) {
	auto position = observers->begin();
	for (Observer* observer : *observers) {
		if (observer == observer_to_delete) {
			observers->erase(position);
			break;
		}
		position = position++;
	}
}

void Subject::notify() {
	for (auto observer : *observers) {
		observer->update(); // As soon as notified, we call update from observer
	}
}

//Observer class implementation
Observer::Observer(Subject* model) {
	model->attach(this);
}
Observer::~Observer() {
};


ConcreteObserver::ConcreteObserver(ConcreteSubject* player, void (*callback)(ConcreteSubject*)) : Observer(player) {
	this->player = player;
	this->callback = callback;
}

ConcreteObserver::~ConcreteObserver() {

	player->detach(this);
	player = nullptr;
	callback = nullptr;
}

void ConcreteObserver::update() {
	callback(player);
}