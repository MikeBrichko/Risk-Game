#include "GameObservers.h"
#include <list>
#include <iostream>

using namespace std;


//Observer class implementation
Observer::Observer(){
};

Observer::~Observer(){
};

void Observer::update() {
	std::cout << "Empty";
}

//Subject class implementation
Subject::Subject()
{
	observers = new list<Observer*>;
}

Subject::~Subject()
{
	delete observers;
}

void Subject::attach(Observer* o)
{
	observers->push_back(o);
};

void Subject::detach(Observer* o)
{
	observers->remove(o);
};

void Subject::notify()
{
	list<Observer*>::iterator i = observers->begin();
	for (; i != observers->end(); i++)
	{
		(*i)->update();
	}
}

std::list<Observer*>* Subject::getObservers() {
	return observers;
};
