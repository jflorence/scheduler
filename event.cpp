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
#include "processor.h"

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

void StopSimulation::print()
{
	std::cout << getTime() <<": StopSimulation\n";
}

NewProcess::~NewProcess()
{
}

void NewProcess::queueProcess(Process *task)
{
	Queue::getReadyQueue()->add(task);
}

void NewInteractiveProcess::process()
{
	task = createTask();
	queueProcess(task);	
	scheduleNextEvent();
	LOG("task "<<task->getPid()<<" created");
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
	return;
}

Process *NewInteractiveProcess::createTask()
{
	double cpuLambda = 1.0/5;
	double ioLambda = 1.0/10;
	return Process::createProcess(cpuLambda, ioLambda);
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
	Event *e = new NewInteractiveProcess(time+interval, nullptr, false);
	EventList::getInstance()->insert(e);
}

void NewInteractiveProcess::print()
{
	std::cout << getTime() << ": New interactive process\n";
}

void NewJob::process()
{
	/*TODO: refactor private functions to the parent class*/
	if (task == nullptr)
		task = createTask();
	queueProcess(task);
	scheduleNextEvent();
	LOG("job "<<task->getPid()<< "created");
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
	return;
}

Process *NewJob::createTask()
{
	Process *p = Process::createRealTimeTask(10, 35, 30, ((pid != -1) ? pid:Process::getNewPid()));

	return p;
}

void NewJob::scheduleNextEvent()
{
	if(!renew)
		return;
	Event *e = new NewJob(time + task->getPeriod(), new Process(*task), false);
	EventList::getInstance()->insert(e);
}

void NewJob::print()
{
	std::cout << getTime() << ": New job with pid "<<task->getPid()<<"\n";
}

void TimeOut::process()
{
	TimeOut *e = new TimeOut(time+interval, task);
	e->setInterval(interval);
	EventList::getInstance()->insert(e);
	LOG("Time out");
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
	return;
}

void TimeOut::setType(TriggeringEvent trigger)
{
	eventType = trigger;
}

double TimeOut::getInterval()
{
	return interval;
}

void TimeOut::setInterval(double inter)
{
	interval = inter;
}

void TimeOut::print()
{
	std::cout << getTime() << ": TimeOut";
	if (eventType == freqUpdate)
	{
		std::cout << " for frequency update";	
	}
	std::cout << "\n";
}

void UsageUpdate::process()
{
	UsageUpdate *e = new UsageUpdate(time+interval, nullptr);
	e->setInterval(interval);
	EventList::getInstance()->insert(e);
	LOG("Usage update");
	/*This event should be independent of the task scheduler?*/
	Processor::getInstance()->updateUsage(TaskScheduler::getInstance()->isBusy());
	return;
}

void UsageUpdate::print()
{
	std::cout << getTime() << ": updating CPU usage\n";
}

void Ready::process()
{
	assert(task != nullptr);
	Queue::getReadyQueue()->add(task);
	Queue::getWaitQueue()->remove(task);
	LOG("task "<<task->getPid()<<" becomes ready");
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
	return;
}

void Ready::print()
{
	std::cout << getTime() << ": process "<<task->getPid()<<" Ready\n";
}

void Waiting::process()
{
	assert(task != nullptr);
	Queue::getWaitQueue()->add(task);
	LOG("task "<<task->getPid()<<" is blocked");
	Event *e = new Ready(time + task->getCurrentIoTime(), task);
	EventList::getInstance()->insert(e);
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
	return;
}

void Waiting::print()
{
	std::cout << getTime() << ": process "<<task->getPid()<<" is waiting\n";
}

void Terminates::process()
{
	assert(task != nullptr);
	LOG("task "<<task->getPid()<<" terminates");
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
	delete task;
	return;
}

void Terminates::print()
{
	std::cout << getTime() << ": process "<<task->getPid()<<" terminates\n";
}







