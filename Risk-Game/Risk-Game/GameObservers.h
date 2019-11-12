#pragma once
#include <list>

typedef enum : int {
	ATTACK,
	REINFORCE,
	FORTIFY,
	GAME_OVER
} Phase;

//Abstract Observer class
class Observer   
{
public:
	~Observer();
	virtual void update();
protected:
	Observer();
};

//Subject class (Observable class)
class Subject 
{
public:
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify();
	std::list<Observer*>* getObservers();
	Subject();
	~Subject();
private:
	std::list<Observer*> *observers;

};
//
//class ConcreteObserver : public Observer//Similar to DigitalClock.h in notes
//{
//	//this is class as the Concrete Observer
//private:
//	virtual void displayVictory(Phase current_phase);
//	virtual void displayStats(Phase current_phase);
//public:
//	//GamePhase(Player* player);
//	//~GamePhase();
//	virtual void update(Phase data);
//};