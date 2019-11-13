#include "GameObservers.h"
#include <list>
#include <iostream>

using namespace std;


//Observer class implementation
Observer::Observer(){
};

Observer::~Observer(){
};

//Subject class implementation
Subject::Subject()
{
	observers = new list<Observer*>;
}

Subject::~Subject()
{
	delete observers;
}
