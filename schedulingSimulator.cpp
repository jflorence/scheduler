#include "schedulingSimulator.h"

#include <ctime>
#include "process.h"
#include "event.h"
#include "eventList.h"
#include "randomGenerator.h"
#include "system.h"

void SchedulingSimulator::createRealTimeTask(double startTime, double period, double deadline, double aow)
{
        Process *p = Process::createRealTimeTask(aow, period, deadline, Process::getNewPid(), startTime + deadline);
        Event *rt = new NewJob(startTime, p);
        EventList::getInstance()->insert(rt);
}

void SchedulingSimulator::createInteractiveProcess(double startTime)
{
	EventList::getInstance()->insert(new NewInteractiveProcess(startTime));
}

void SchedulingSimulator::seedRandomGenerator(time_t seed)
{
	RandomGenerator::getRandomGenerator()->seed(seed);
}



void SchedulingSimulator::endSimulation(double time)
{
        EventList *eventList = EventList::getInstance();;
        Event *stopEvent = new StopSimulation(time);
        eventList->insert(stopEvent);
}

void SchedulingSimulator::setUsageCalculationTimeout(double start, double interval)
{
        UsageUpdate *cpuUsageUpdate = new UsageUpdate(start);
        cpuUsageUpdate->setInterval(interval);
        EventList::getInstance()->insert(cpuUsageUpdate);
}

void SchedulingSimulator::setFreqUpdate(double start, double interval)
{
        FreqUpdate *freqTO = new FreqUpdate(start);
        freqTO->setInterval(interval);
        EventList::getInstance()->insert(freqTO);
}

void SchedulingSimulator::setSchedulerTimeout(double start, double interval)
{
        SchedTimeOut *timeout = new SchedTimeOut(start);
        timeout->setInterval(interval);
        EventList::getInstance()->insert(timeout);
}




void SchedulingSimulator::startScheduler()
{
        EventList *list = EventList::getInstance();
        while(!list->isEmpty())
        {
                /*Event *e = list->pop();
                e->process();
                delete e;*/
                Event *e = list->getHead();
		double timeInterval = e->getTime() - previousTime;
		previousTime = e->getTime();
		System::getInstance()->updateTemperature(timeInterval);
                e->process();
                list->pop();
                delete e;
        }
}




