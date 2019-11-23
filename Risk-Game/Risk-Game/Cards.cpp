#include "Cards.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>

int* Hand::armies;

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
	size = new int(numberOfCountries);
	deck = buildDeck(numberOfCountries);
	shuffle();
}

Deck::~Deck() {
	delete size;
	for (auto card : *deck) {
		delete card;
	}
	delete deck;
}

std::vector<Card*>* Deck::buildDeck(int numberOfCountries) {
	std::vector<Card*>* newDeck = new std::vector<Card*>;
	int totalCards = numberOfCountries - (numberOfCountries % 3);
	for (int i = 0; i < totalCards; i++) {
		if (i < totalCards / 3) {
			CardType* cardType = new CardType(infantry);
			newDeck->push_back(new Card(cardType));
		}
		else if (i < (totalCards * 2 / 3)) {
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

Card* Deck::draw() {
	if (deck->size() == 0) {
		deck = buildDeck(*size);
		shuffle();
	}

	Card* topCard = deck->at(0);
	deck->erase(deck->begin());
	return topCard;
}

void Deck::shuffle() {
	int i = 0;
	srand((unsigned int)time(NULL));
	while (i <= 1000) {
		int randomPosition = rand() % deck->size();
		Card* card = deck->at(randomPosition);
		deck->erase(deck->begin() + randomPosition);
		deck->push_back(card);
		i++;
	}
}

int Deck::getDeckSize() {
	return static_cast<int>(deck->size());
}

//----------------------------------------------------------------------------------------
Hand::Hand(std::string* name) {
	hand = new std::vector<Card*>;
	armies = new int(0);
	playerName = name;
}

Hand::~Hand() {
	for (auto card : *hand) {
		delete card;
	}
	delete hand;
	delete armies;
	delete playerName;
}

int Hand::exchange() {
	if (hand->size() < 3)
		return 0;

	//Determine the position and the amount of each CardType that the hand contains
	std::string exchangeArray[3] = {};
	for (int i = 0; i < hand->size(); i++) {
		if (*(hand->at(i)->getCardType()) == "infantry" && exchangeArray[0].size() != 3)
			exchangeArray[0] += i;
		else if (*(hand->at(i)->getCardType()) == "artillery" && exchangeArray[0].size() != 3)
			exchangeArray[1] += i;
		else if (*(hand->at(i)->getCardType()) == "cavalry" && exchangeArray[0].size() != 3)
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
		return increasePlayersArmies();
		break;

	case 2:
		removeCardsInHand(differentCardTypes);
		return increasePlayersArmies();
		break;

	default:
		break;
	}
	return 0;
}

int Hand::exchangeDecision(std::string similarCardTypes, std::string differentCardTypes){
	if (differentCardTypes.size() != 3 && similarCardTypes.size() != 3)
		return 0;

	int choice = 0;
	while (true) {
		std::cout << std::endl;
		std::cout << *playerName << std::endl;

		if (hand->size() != 5)
			std::cout << "Input 0 to not trade cards for armies" << std::endl;

		if (similarCardTypes.size() == 3)
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
	std::cout << "Before" << std::endl;
	printCardsInHand();
	double indexModifier = 0;
	std::sort(cardsInHand.begin(), cardsInHand.end());
	for (int i = 0; i < cardsInHand.length(); i++) {
		if (i == 0) {
			delete hand->at((int)cardsInHand.at(i));
			hand->erase(hand->begin() + (int)cardsInHand.at(i));
		}
		else {
			delete hand->at(static_cast<unsigned __int64>(cardsInHand.at(i) - indexModifier));
			hand->erase(hand->begin() + (static_cast<__int64>(cardsInHand.at(i) - indexModifier)));
		}
		indexModifier += 1;
	}
	std::cout << "After" << std::endl;
	printCardsInHand();
}

int Hand::increasePlayersArmies() {
	*Hand::armies += 5;
	std::cout << std::endl << "The amount of armies " << *playerName << " received is " << *armies << std::endl << std::endl;
	return *armies;
} 

int Hand::addCard(Card* card) {
	std::cout << "The card " << *playerName << " drew is a " << *card->getCardType() << " card!" << std::endl;
	hand->push_back(card);
	return exchange();
}

void Hand::printCardsInHand() {
	std::cout << "The cards you have in your hand are : ";
	for (auto card : *hand) {
		std::cout << *card->getCardType() << " ";
	}
	std::cout << std::endl;
}

