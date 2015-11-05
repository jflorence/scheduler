#include <iostream>
#include <list>
#include "event.h"
#include "process.h"
#include <tuple>
#include "eventList.h"
#include <ctime>
#include "randomGenerator.h"


void startEventScheduler()
{
	EventList *list = EventList::getInstance();
	while(!list->isEmpty())
	{
		/*Event *e = list->pop();
		e->process();
		delete e;*/
		Event *e = list->getHead();
		e->process();
		list->pop();
		delete e;
	}
}


void createRealTimeTask(double startTime, double period, double deadline, double aow)
{
	Process *p = Process::createRealTimeTask(aow, period, deadline, Process::getNewPid());
	Event *rt = new NewJob(startTime, p);
	EventList::getInstance()->insert(rt);
}

int main()
{
	std::cout << "Hello!\n";
	RandomGenerator::getRandomGenerator()->seed(time(NULL));
	
	EventList *eventList = EventList::getInstance();;	
	Event *stopEvent = new StopSimulation(100, nullptr);
	eventList->insert(stopEvent);
	eventList->setEndTime(100.0);
	
	Event *interactive = new NewInteractiveProcess(1, nullptr);
	eventList->insert(interactive);
	interactive = new NewInteractiveProcess(1, nullptr);
	eventList->insert(interactive);

	createRealTimeTask(2, 35, 30, 10);

	Event *timeout = new TimeOut(1, nullptr);
	eventList->insert(timeout);

	TimeOut *freqTO = new TimeOut(0, nullptr);
	freqTO->setType(TriggeringEvent::freqUpdate);
	eventList->insert(freqTO);
/*
	Event *cpuUsageUpdate = new UsageUpdate(1, nullptr);
	eventList->insert(cpuUsageUpdate);
*/

	startEventScheduler();

	return 0;
}

































