#pragma once
#include <list>

//Abstract class Observer
class Observer   
{
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};


//Class Subject (Observable)
class Subject 
{
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	~Subject();
private:
	std::list<Observer*> *_observers;

};