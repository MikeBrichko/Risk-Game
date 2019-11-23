#pragma once
#include <list>
#include <iostream>
#include "Map.h"

typedef enum : int {
	ATTACK,
	REINFORCE,
	FORTIFY,
	GAME_OVER,
	DEFEATED,
	LOSE_COUNTRY
} Phase;

class Observer;
//Subject class (Observable class)
class Subject
{
public:
	void attach(Observer* o);
	void detach(Observer* o);
	void notify();
	Subject();
	~Subject();
protected:
	std::list<Observer*>* observers; // In order to see from the parents
};
//Abstract Observer class
class Observer
{
public:
	Observer(Subject* model);
	~Observer();
	virtual void update() = 0;

};

class ConcreteSubject : public Subject {
public:
	virtual Phase getPhase() = 0;
	virtual std::string getCurrentPlayerName() = 0;
	virtual std::string getDefeatedCountryName() = 0;
	virtual std::vector<std::string*> getStats() = 0;
};

class ConcreteObserver : public Observer {
public:
	ConcreteObserver(ConcreteSubject* player, void (*display_callback)(ConcreteSubject*));
	~ConcreteObserver();
	void update() override;
	void (*callback)(ConcreteSubject*);
private:
	ConcreteSubject* player;
};