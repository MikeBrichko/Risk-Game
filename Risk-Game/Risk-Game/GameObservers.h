#pragma once
#include <list>
#include <iostream>

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
	//virtual void update() = 0;
	virtual void update(std::string name, Phase phase) = 0;

protected:
	Observer();
};

//Subject class (Observable class)
class Subject 
{
public:
	virtual void attachObserver(Observer* o) = 0;
	virtual void detachObserver(Observer* o) = 0;
	virtual void notifyObservers() = 0;
	Subject();
	~Subject();
protected:
	std::list<Observer*>* observers; // In order to see from the parents

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