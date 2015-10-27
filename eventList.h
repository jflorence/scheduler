#ifndef EVENTLIST_H
#define EVENTLIST_H

#include <list>
#include "event.h"
class Event;

class EventList
{

public:
	Event *pop();
	std::list<Event *>::iterator insert(Event *e);
	void remove(std::list<Event *>::iterator p);
	bool isEmpty();
private:
	std::list<Event *> list;
};






#endif
