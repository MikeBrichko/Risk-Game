#pragma once
#include <list>
#include "Player.h"

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
	virtual void Update(Phase data) = 0;
protected:
	Observer();
};

//Subject class (Observable class)
class Subject 
{
public:
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify(Phase data);
	Subject();
	~Subject();
private:
	std::list<Observer*> *_observers;

};

class GamePhase : public Observer//Similar to DigitalClock.h in notes
{
	//this is class as the Concrete Observer
private:
	Player* player;
	void displayVictory(Phase current_phase);
	void displayStats(Phase current_phase);
public:
	GamePhase(Player* player);
	~GamePhase();
	void Update(Phase data);
};