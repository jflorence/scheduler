#ifndef EVENTLIST_H
#define EVENTLIST_H

#include <list>
#include "event.h"
class Event;

class EventList
{

public:
	typedef std::list<Event *>::iterator iterator;
	static EventList *getInstance();
	Event *pop();
	std::list<Event *>::iterator insert(Event *e);
	void remove(std::list<Event *>::iterator p);
	bool isEmpty();
	void setEndTime(double time);
	std::list<Event *>::iterator end();
private:
	static EventList *instance;
	std::list<Event *> list;
	double endTime;
};






#endif
