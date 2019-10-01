#pragma once


#include <iostream>
#include <vector>
#include <istream>
//
//namespace Dice
//{
	class Dice
	{
	public:
		/*std::vector<int>* tracking;*/
		void storedDiceValue(int* addedValue);
		Dice();
		int* rollDice();
		void printCurrentState();
	private:
		int* percentDice;
		int* numOfRolls;
	};
//
//	class HowManyDice {
//	public:
//		void setNumOfDice(int* numOfDice);
//		int getNumOfDice();
//	private:
//		int val;
//	};
//}