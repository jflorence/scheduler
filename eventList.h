#ifndef EVENTLIST_H
#define EVENTLIST_H

#include <cmath>
#include <list>

#include "event.h"

class Event;

class EventList
{

public:
	typedef std::list<Event *>::iterator iterator;
	static EventList *getInstance();
	Event *pop();
	Event *getHead();
	Event *insert(Event *e);
	void remove(Event *e);
	void empty();
	bool isEmpty();
	void print();
private:
	static EventList *instance;
	std::list<Event *> list;
	double endTime{INFINITY};
	bool emptied{false};
};






#endif
