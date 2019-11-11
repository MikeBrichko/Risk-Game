#pragma once
#include "Player.h"
#include <string>
#include <vector>

class Player;

class Strategy {
public:
	Strategy();
	virtual void reinforce(Player* player) {};
	virtual void attack(Player* player, std::vector<Player*>* players) {};
	virtual void fortify(Player* player) {};
};

class HumanPlayer : public Strategy {
public:
	HumanPlayer();
	void reinforce(Player* player);
	void attack(Player* player, std::vector<Player*>* players);
	void fortify(Player* player);
};

class AggressiveComputer : public Strategy {
private:
	Country* getStrongestCountry(std::vector<Country*>* countries);
public:
	AggressiveComputer();
	void reinforce(Player* player);
	void attack(Player* player, std::vector<Player*>* players);
	void fortify(Player* player);
};

class BenevolentComputer : public Strategy {
private: 
	Country* getWeakestCountry(std::vector<Country*>* countries);
public:
	BenevolentComputer();
	void reinforce(Player* player);
	void fortify(Player* player);
};
