#include "eventList.h"

EventList *EventList::instance = nullptr;

EventList *EventList::getInstance()
{
	if (instance == nullptr)
	{
		instance = new EventList();
	}
	return instance;
}

Event *EventList::pop()
{
	Event *e = list.front();
	list.pop_front();
	return e;
}


std::list<Event *>::iterator EventList::insert(Event *e)
{
	double time = e->getTime();
	auto p = list.end();
	while(p != list.begin())
	{
		if ((*--p)->getTime() < time)
		{
			p++;
			break;
		}
	}
	auto i = list.insert(p, e);
	return i;
}



void EventList::remove(std::list<Event *>::iterator p)
{
	list.erase(p);
}


bool EventList::isEmpty()
{
	return (list.begin() == list.end());
}











