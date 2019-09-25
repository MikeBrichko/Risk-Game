#pragma once
#include <string>
#include <vector>
#include <map>

enum CardType {infantry, artillary, cavalry};

class Card {
private:
	CardType* cardType;
	std::map<int, std::string>* cardTypeMap;

public:
	Card(CardType* type);
	~Card();
	std::string* getCardType();
}; 

class Deck {
private:
	std::vector<Card*>* deck;
	std::vector<Card*>* buildDeck(int);
	void shuffle();

public:
	Deck(int);
	~Deck();
	Card* draw(int);
};

class Hand {
private:
	std::vector<Card*>* hand;
	int* armies;

public:
	Hand();
	void exchange();
	int* getArmySize();
	void increaseArmySize();
	void addCard(Card*);
	
};