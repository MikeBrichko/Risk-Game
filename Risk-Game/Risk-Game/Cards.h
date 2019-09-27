#pragma once
#include <string>
#include <vector>
#include <map>

enum CardType {infantry, artillery, cavalry};

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
	int getDeckSize();
};

class Hand {
private:
	std::vector<Card*>* hand;
	int* armies;
	std::string* playerName;
	void removeCardsInHand(std::string);
	int exchangeDecision(std::string, std::string);
	void increasePlayersArmies(std::vector<Hand*>*);
	void printCardsInHand();
	void exchange(std::vector<Hand*>*);

public:
	Hand(std::string*);
	~Hand();
	void addCard(Card*, std::vector<Hand*>*);
};