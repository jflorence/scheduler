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
	Event *stopEvent = new StopSimulation(100, NULL, false);
	eventList->insert(stopEvent);

	
	Event *interactive = new NewInteractiveProcess(1, NULL, true);
	eventList->insert(interactive);
	
	startEventScheduler();

	return 0;
}































