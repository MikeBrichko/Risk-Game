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
	cardTypeMap->insert(std::pair<int, std::string>(1, "artillery"));
	cardTypeMap->insert(std::pair<int, std::string>(2, "cavalry"));
};

Card::~Card() {
	delete cardType;
	delete cardTypeMap;
}

std::string* Card::getCardType() {
	return &(cardTypeMap->find(*cardType)->second);
};

//----------------------------------------------------------------------------------------
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
			CardType* cardType = new CardType(artillery);
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

int Deck::getDeckSize() {
	return deck->size();
}

//----------------------------------------------------------------------------------------
Hand::Hand(std::string* name) {
	hand = new std::vector<Card*>;
	armies = new int(0);
	playerName = name;
}

void Hand::exchange() {
	if (hand->size() < 3)
		return;

	//Determine the position and the amount of each CardType that the hand contains
	std::string exchangeArray[3] = {};
	for (int i = 0; i < hand->size(); i++) {
		if (*(hand->at(i)->getCardType()) == "infantry")
			exchangeArray[0] += i;
		else if (*(hand->at(i)->getCardType()) == "artillery")
			exchangeArray[1] += i;
		else
			exchangeArray[2] += i;
	};
	
	//Determine the set of cards that can be traded
	std::string differentCardTypes = "";
	std::string similarCardTypes = "";
	for (int i = 0; i < 3; i++) {
		if (exchangeArray[i].length() > 0)
			differentCardTypes += exchangeArray[i].at(0);

		if (exchangeArray[i].length() == 3) 
			similarCardTypes = exchangeArray[i];
	}

	//Prompt user if he would like to exchange cards for armies
	switch (exchangeDecision(similarCardTypes, differentCardTypes)) {
	case 0:
		break;

	case 1:
		removeCardsInHand(similarCardTypes);
		increaseArmySize();
		break;

	case 2:
		removeCardsInHand(differentCardTypes);
		increaseArmySize();
		break;

	default:
		break;
	}
}

int Hand::exchangeDecision(std::string similarCardTypes, std::string differentCardTypes){
	if (differentCardTypes.size() != 3 && similarCardTypes.size() < 3)
		return 0;

	int choice = 0;
	while (true) {
		std::cout << std::endl;
		std::cout << *playerName << std::endl;

		if (hand->size() != 5)
			std::cout << "Input 0 to not trade cards for armies" << std::endl;

		if (similarCardTypes.size() >= 3)
			std::cout << "Input 1 to trade all similar cards" << std::endl;

		if (differentCardTypes.size() == 3) 
			std::cout << "Input 2 to trade all different cards" << std::endl;

		std::cin >> choice;
		std::cout << std::endl;

		if (hand->size()==5 && choice != 1 && choice != 2) {
			std::cout << *playerName << std::endl;
			std::cout << "You have 5 cards in hand. You need to trade your cards for armies. Game rules are fun :)" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			return choice;
		}
	}
}

void Hand::removeCardsInHand(std::string cardsInHand) {
	int indexModifier = 0;
	std::sort(cardsInHand.begin(), cardsInHand.end());
	for (int i = 0; i < cardsInHand.length(); i++) {
		if (i == 0)
			hand->erase(hand->begin() + (int)cardsInHand.at(i));
		else
			hand->erase(hand->begin() + (static_cast<double>(cardsInHand.at(i)) - indexModifier));
		indexModifier += 1;
	}
}

int* Hand::getArmySize() {
	return armies;
}

int Hand::getHandSize() {
	return hand->size();
}

void Hand::increaseArmySize() {
	*armies += 5;
	std::cout << "The amount of armies "<< *playerName << " receives is " << *armies << std::endl;
}

void Hand::addCard(Card* card) {
	std::cout << "The card " << *playerName << " drew is a " << *card->getCardType() << " card!" << std::endl;
	hand->push_back(card);
	exchange();
}

