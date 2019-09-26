#include "Cards.h"
#include<iostream>
#include <time.h>

int main() {
	std::cout << "Demonstrating creation of Deck with the same amount of card types (infantry, artillery, cavalry)" << std::endl;
	int numberOfCountries = 0;
	std::cout << "Enter the amount of countries on the board" << std::endl;
	std::cin >> numberOfCountries;

	Deck* deck = new Deck(numberOfCountries);
	int amountOfEachCardType[3] = {};
	while (deck->getDeckSize() != 0) {
		Card* card = deck->draw(numberOfCountries);
		if (*(card->getCardType()) == "infantry") {
			amountOfEachCardType[0] += 1;
		} else if (*(card->getCardType()) == "artillery") {
			amountOfEachCardType[1] += 1;
		} else if (*(card->getCardType()) == "cavalry") {
			amountOfEachCardType[2] += 1;
		}
	}

	std::cout << "Amount of infantry in the deck: " << amountOfEachCardType[0] << std::endl;
	std::cout << "Amount of artillery in the deck: " << amountOfEachCardType[1] << std::endl;
	std::cout << "Amount of cavalery in the deck: " << amountOfEachCardType[2] << std::endl;
	std::cout << "We have built a deck with equal amounts of infantry, artilary and cavalry cards" << std::endl;

	std::cout << std::endl << "Demonstrating the draw() method" << std::endl;
	std::cout << "Deck size before drawing a card: " << deck->getDeckSize() << std::endl;
	std::cout << "Drawing a card" << std::endl;
	Card* card = deck->draw(numberOfCountries);
	std::cout << "Deck size after drawing a card: " << deck->getDeckSize() << std::endl;
	std::cout << "The Card that was drawn was a " << *(card->getCardType()) << " card." << std::endl;

	std::cout <<std::endl << "Demonstrating the addition of a card into a players hand" << std::endl;
	Hand* hand = new Hand(new std::string("Mike"));
	std::cout << "Hand size before adding a card: " << hand->getHandSize() << std::endl;
	std::cout << "Adding the card in the Hand of Mike" << std::endl;
	hand->addCard(card);
	std::cout << "Hand size after adding a card: " << hand->getHandSize() << std::endl;


	std::cout << std::endl << "Demonstrating the exchange() method" << std::endl;
	while (true) {
		hand->addCard(deck->draw(numberOfCountries));
	}

	return 0;
}