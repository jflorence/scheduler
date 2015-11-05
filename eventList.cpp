#include "eventList.h"
#include <cassert>
#include <iostream>
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


Event * EventList::insert(Event *e)
{
	if (e == nullptr)
		return nullptr;
	double time = e->getTime();
	

	if(time > endTime)
	{
		delete e;
		return nullptr;
	}

	
	auto p = list.end();
	while(p != list.begin())
	{
		if ((*--p)->getTime() < time)
		{
			p++;
			break;
		}
	}
	auto it = list.insert(p, e);
	assert(e == (*it));
	return e;
}



void EventList::remove(Event *e)
{
	for (auto it = list.begin(); it != list.end(); it++)
	{
		(*it)->print();
		if (e == (*it))
		if (e == (*it))
		{
			assert(e != nullptr);
			list.erase(it);
			return;
		}
	}
}


bool EventList::isEmpty()
{
	return (emptied ? true : (list.begin() == list.end()));
}

void EventList::empty()
{
	emptied = true;
}


void EventList::print()
{
	std::cout << "Printing the event list:\n";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		assert((*it) != nullptr);
		std::cout << "    ";
		(*it)->print();
	}
}


Event *EventList::getHead()
{
	return (*list.begin());
}


























