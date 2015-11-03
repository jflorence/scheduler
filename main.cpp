#include <iostream>
#include <list>
#include "event.h"
#include "process.h"
#include <tuple>
#include "eventList.h"


void startEventScheduler()
{
	EventList *list = EventList::getInstance();
	while(!list->isEmpty())
	{
		Event *e = list->pop();
		e->process();
		delete e;
	}
}


int main()
{
	std::cout << "Hello!\n";
	
	EventList *eventList = EventList::getInstance();;	
	Event *stopEvent = new StopSimulation(100, NULL);
	eventList->insert(stopEvent);
	eventList->setEndTime(100.0);
	
	Event *interactive = new NewInteractiveProcess(1, NULL);
	eventList->insert(interactive);
	interactive = new NewInteractiveProcess(1, NULL);
	eventList->insert(interactive);

	Event *timeout = new TimeOut(1, NULL);
	eventList->insert(timeout);
	
	startEventScheduler();

	return 0;
}

































