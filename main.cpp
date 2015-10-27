#include <iostream>
#include <list>
#include "event.h"
#include "process.h"
#include <tuple>
#include "eventList.h"


void scheduleTask(bool preempt)
{
	
}

void startEventScheduler(EventList *list)
{
	bool keepRunning = true;
	while(!list->isEmpty())
	{
		Event *e = list->pop();
		bool preempt = e->process(list);
		scheduleTask(preempt);
		delete e;
	}
}


int main()
{
	EventList eventList;	
	Event *stopEvent = new StopSimulation(100, NULL);
	eventList.insert(stopEvent);

	std::cout << "Hello!\n";
	
	Event *interactive = new NewInteractiveProcess(1, NULL, false);
	eventList.insert(interactive);
	startEventScheduler(&eventList);

	return 0;
}































