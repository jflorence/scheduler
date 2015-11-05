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

void endSimulation(double time)
{
	EventList *eventList = EventList::getInstance();;	
	Event *stopEvent = new StopSimulation(time);
	eventList->insert(stopEvent);
}

void setUsageCalculationTimeout(double start, double interval)
{
	UsageUpdate *cpuUsageUpdate = new UsageUpdate(start);
	cpuUsageUpdate->setInterval(interval);
	EventList::getInstance()->insert(cpuUsageUpdate);
}

void setFreqUpdate(double start, double interval)
{
	FreqUpdate *freqTO = new FreqUpdate(start);
	freqTO->setInterval(interval);
	EventList::getInstance()->insert(freqTO);
}

void setSchedulerTimeout(double start, double interval)
{
	TimeOut *timeout = new TimeOut(start);
	timeout->setInterval(interval);
	EventList::getInstance()->insert(timeout);
}

int main()
{
	std::cout << "Hello!\n";
	
	RandomGenerator::getRandomGenerator()->seed(time(NULL));
	
	EventList::getInstance()->insert(new NewInteractiveProcess(0.0));
	EventList::getInstance()->insert(new NewInteractiveProcess(0.0));
	createRealTimeTask(2.0, 35.0, 30.0, 10.0);

	setUsageCalculationTimeout(1.0, 2.0);
	setFreqUpdate(1.0, 10.0);
	setSchedulerTimeout(1.0, 2.0);
	endSimulation(100.0);	

	startEventScheduler();

	return 0;
}

































