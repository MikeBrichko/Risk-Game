#include "Cards.h"
#include<iostream>
#include <time.h>

int main() {
	Deck* testDeck = new Deck(60);
	Hand* testHand = new Hand();
	std::cout << "We have built a deck with equal amounts of infantry, artilary and cavalry cards" << std::endl;

	while (true) {
		testHand->addCard(testDeck->draw(60));
	}

	return 0;
}