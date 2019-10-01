#pragma once
#ifndef DICE_H
#define DICE_H


#include <iostream>
#include <vector>
using std::istream;
using std::ostream;


namespace Dice
{
	class EachDice
	{
	public:
		std::vector<int>* tracking;
		int* percentDice[6];
		int* numOfRolls;
		void storedDiceValue(int* addedValue);
		EachDice();
		int rollDice();
		void printCurrentState();
	private:

	};

	class HowManyDice {
	public:
		void setNumOfDice(int* numOfDice);
		int getNumOfDice();
	private:
		int val;
	};
} 
#endif