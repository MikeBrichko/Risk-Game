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
	int* size;
	std::vector<Card*>* deck;
	std::vector<Card*>* buildDeck(int);
	void shuffle();

public:
	Deck(int);
	~Deck();
	Card* draw();
	int getDeckSize();
};

class Hand {
private:
	std::vector<Card*>* hand;
	static int* armies;
	std::string* playerName;
	void removeCardsInHand(std::string);
	int exchangeDecision(std::string, std::string);

	// We have to change void to return int
	int increasePlayersArmies();
	int exchange();

public:
	Hand(std::string*);
	~Hand();
	int addCard(Card*);
	void printCardsInHand();
};