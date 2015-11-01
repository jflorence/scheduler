#include "event.h"
#include <iostream>
#include <cassert>
#include "process.h"
#include "log.h"
#include "queue.h"
#include "eventList.h"
#include "randomGenerator.h"
#include "taskScheduler.h"
#include "eventType.h"


Event::Event(double t, Process *p, bool r)
{
	time = t;
	task = p;
	renew = r;
}

Event::~Event()
{
}

double Event::getTime()
{
	return time;
}


void StopSimulation::process()
{
	LOG("Simulation stopped");
	return;
}

void NewInteractiveProcess::process()
{
	task = createTask();
	queueProcess(task);	
	scheduleNextEvent();
	LOG("task "<<task->getPid()<<" created");
	TaskScheduler::getInstance()->scheduleTask(TriggeringEvent::newprocess, time);
	return;
}

Process *NewInteractiveProcess::createTask()
{
	double cpuLambda = 1.0/5;
	double ioLambda = 1.0/10;
	return Process::createProcess(cpuLambda, ioLambda);
}

void NewInteractiveProcess::queueProcess(Process *p)
{
	Queue::getReadyQueue()->add(p);
}

void NewInteractiveProcess::scheduleNextEvent()
{
	if (!renew)
	{
		return;
	}
	//The mean duration of a process is nbBursts*(5+10) = 150.
	double lambda = 1.0/150;
	double interval;
	do
	{
		RandomGenerator *gen = RandomGenerator::getRandomGenerator();
		interval = gen->drawExp(lambda);
	} while(interval == std::numeric_limits<double>::infinity());
	Event *e = new NewInteractiveProcess(time+interval, NULL, false);
	EventList::getInstance()->insert(e);
}

void NewJob::process()
{
/*TODO*/
	return;
}

void TimeOut::process()
{
	Event *e = new TimeOut(time+interval, task);
	EventList::getInstance()->insert(e);
	LOG("Time out");
	TaskScheduler::getInstance()->scheduleTask(TriggeringEvent::timeout, time);
	return;
}

double TimeOut::getInterval()
{
	return interval;
}

void TimeOut::setInterval(double inter)
{
	interval = inter;
}

void Ready::process()
{
	assert(task != nullptr);
	Queue::getReadyQueue()->add(task);
	Queue::getWaitQueue()->remove(task);
	LOG("task "<<task->getPid()<<" becomes ready");
	TaskScheduler::getInstance()->scheduleTask(TriggeringEvent::ready, time);
	return;
}

void Waiting::process()
{
	assert(task != nullptr);
	Queue::getWaitQueue()->add(task);
	LOG("task "<<task->getPid()<<" is blocked");
	Event *e = new Ready(time + task->getCurrentIoTime(), task);
	EventList::getInstance()->insert(e);
	TaskScheduler::getInstance()->scheduleTask(TriggeringEvent::wait, time);
	return;
}

void Terminates::process()
{
	assert(task != nullptr);
	LOG("task "<<task->getPid()<<" terminates");
	TaskScheduler::getInstance()->scheduleTask(TriggeringEvent::terminate, time);
	//delete task;
	return;
}









