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
	TaskScheduler::getInstance()->scheduleTask(TriggeringEvent::newprocess, time);
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

void TimeOut::print()
{
	std::cout << getTime() << ": TimeOut\n";
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
	TaskScheduler::getInstance()->scheduleTask(TriggeringEvent::wait, time);
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
	TaskScheduler::getInstance()->scheduleTask(TriggeringEvent::terminate, time);
	delete task;
	return;
}

void Terminates::print()
{
	std::cout << getTime() << ": prcess "<<task->getPid()<<" terminates\n";
}







