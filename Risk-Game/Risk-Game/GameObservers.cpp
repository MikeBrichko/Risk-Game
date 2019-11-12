#include "GameObservers.h"
#include <list>

using namespace std;


//Observer class implementation
Observer::Observer(){
};

Observer::~Observer(){
};



//Subject class implementation
Subject::Subject()
{
	_observers = new list<Observer*>;
}

Subject::~Subject()
{
	delete _observers;
}

void Subject::attach(Observer* o)
{
	_observers->push_back(o);
};

void Subject::detach(Observer* o)
{
	_observers->remove(o);
};

void Subject::notify(Phase data)
{
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); i++)
	{
		(*i)->Update(data);
	}
}

GamePhase::GamePhase(Player* player) {
	this->player = player;
	player->attach(this);
}

GamePhase::~GamePhase() {
	player->detach(this); 
}

void GamePhase::Update(Phase data) {
	if (data == GAME_OVER)
		displayVictory(data);
	else
		displayStats(data);
}

void GamePhase::displayStats(Phase data) {
	string phase;
	switch (data) {
	case Phase::ATTACK:
		phase = "ATTACK PHASE";
		break;
	case Phase::REINFORCE:
		phase = "REINFORCEMENT PHASE";
		break;
	case Phase::FORTIFY:
		phase = "FORTIFY PHASE";
		break;
	default:
		phase = "UNDEFINED PHASE";
	}

	cout << "********** " << this->player->getPlayerID() << " : " << phase << " **********" << endl;
}

void GamePhase::displayVictory(Phase data) {

}