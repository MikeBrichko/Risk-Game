#include "Cards.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>

//----------------------------------------------------------------------------------------
Card::Card(CardType* type) {
	cardType = type;
	cardTypeMap = new std::map<int, std::string>();
	cardTypeMap->insert(std::pair<int, std::string>(0, "infantry"));
	cardTypeMap->insert(std::pair<int, std::string>(1, "artillary"));
	cardTypeMap->insert(std::pair<int, std::string>(2, "cavalry"));
};

Card::~Card() {
	delete cardType;
	delete cardTypeMap;
}

std::string* Card::getCardType() {
	return &(cardTypeMap->find(*cardType)->second);
};

//-------------------------------------------------------------------------------------------
Deck::Deck(int numberOfCountries) {
	deck = buildDeck(numberOfCountries);
	shuffle();
}

Deck::~Deck() {
	for (auto pointer : *deck) {
		delete pointer;
	}
	delete deck;
}

std::vector<Card*>* Deck::buildDeck(int numberOfCountries) {
	std::vector<Card*>* newDeck = new std::vector<Card*>;
	for (int i = 0; i < numberOfCountries; i++) {
		if (i < numberOfCountries / 3) {
			CardType* cardType = new CardType(infantry);
			newDeck->push_back(new Card(cardType));
		}
		else if (i < (numberOfCountries * 2 / 3)) {
			CardType* cardType = new CardType(artillary);
			newDeck->push_back(new Card(cardType));
		}
		else {
			CardType* cardType = new CardType(cavalry);
			newDeck->push_back(new Card(cardType));
		}
	}
	return newDeck;
}

Card* Deck::draw(int numberOfCountries) {
	if (deck->size() == 0) {
		deck = buildDeck(numberOfCountries);
		shuffle();
	}

	Card* topCard = deck->at(0);
	deck->erase(deck->begin());
	return topCard;
}

void Deck::shuffle() {
	int i = 0;
	srand(time(0));
	while (i <= 1000) {
		int randomPosition = rand() % deck->size();
		Card* card = deck->at(randomPosition);
		deck->erase(deck->begin() + randomPosition);
		deck->push_back(card);
		i++;
	}
}

//----------------------------------------------------------------------------------------
Hand::Hand() {
	hand = new std::vector<Card*>;
	armies = new int(0);
}

void Hand::exchange() {
	int armySize = 0;
	std::string exchangeArray[3] = {};
	
	if (hand->size() < 3)
		return;

	//Determine the position and the amount of each CardType that the hand contains
	for (int i = 0; i < hand->size(); i++) {
		if (*(hand->at(i)->getCardType()) == "infantry")
			exchangeArray[0] += i;
		else if (*(hand->at(i)->getCardType()) == "artillary")
			exchangeArray[1] += i;
		else
			exchangeArray[2] += i;
	};
	
	//Determine the cards that can be traded
	std::string setOfDifferentCardTypes = "";
	std::string setOfSimilarCardTypes = "";
	for (int i = 0; i < 3; i++) {
		if (exchangeArray[i].length() > 0)
			setOfDifferentCardTypes += exchangeArray[i].at(0);

		if (exchangeArray[i].length() == 3) 
			setOfSimilarCardTypes = exchangeArray[i];
	}

	int choice = 0;
	if (setOfDifferentCardTypes.size() == 3 && setOfSimilarCardTypes.size() >= 3) {
		std::cout << "Input 1 to trade all similar cards or Input 2 to trade all different cards or Input nothing to not trade cards for armies" << std::endl;
		std::cin >> choice;
	}
	else if (setOfDifferentCardTypes.size() != 3 && setOfSimilarCardTypes.size() >= 3) {
		std::cout << "Enter 1 to trade all similar cards or Input nothing to not trade cards for armies" << std::endl;
		std::cin >> choice;
	}
	else if (setOfDifferentCardTypes.size() == 3 && setOfSimilarCardTypes.size() < 3) {
		std::cout << "Enter 2 to trade all different cards or Input nothing to not trade cards for armies" << std::endl;
		std::cin >> choice;
	}

	int indexModifier = 0;
	switch (choice)
	{
	case 1: 
		std::sort(setOfSimilarCardTypes.begin(), setOfSimilarCardTypes.end());
		for (int i = 0; i < setOfSimilarCardTypes.length(); i++) {
			if (i == 0)
				hand->erase(hand->begin() + (int)setOfSimilarCardTypes.at(i));
			else
				hand->erase(hand->begin() + ((int)setOfDifferentCardTypes.at(i) - indexModifier));
			indexModifier += 1;
		}
		increaseArmySize();
		std::cout << "The amount of armies you receive is " << *armies << std::endl;
		break;

	case 2: 
		std::sort(setOfDifferentCardTypes.begin(), setOfDifferentCardTypes.end());
		for (int i = 0; i < setOfDifferentCardTypes.length(); i++) {
			if (i==0 || (int)setOfDifferentCardTypes.at(i) == 0)
				hand->erase(hand->begin() + (int)setOfDifferentCardTypes.at(i));
			else
				hand->erase(hand->begin() + (((int)setOfDifferentCardTypes.at(i)) - indexModifier));
			indexModifier += 1;
		}
		increaseArmySize();
		std::cout << "The amount of armies you receive is " << *armies << std::endl;
		break;

	default: 
		return;
		break;
	}
}

int* Hand::getArmySize() {
	return armies;
}

void Hand::increaseArmySize() {
	*armies += 5;
}

void Hand::addCard(Card* card) {
	hand->push_back(card);
	exchange();
}

