#pragma once
#include <list>

using namespace std;


//Abstract Observer class
class Observer   
{
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};


//Subject class (Observable class)
class Subject 
{
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	~Subject();
private:
	list<Observer*> *_observers;

};