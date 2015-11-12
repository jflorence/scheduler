#include "event.h"

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "eventList.h"
#include "eventType.h"
#include "log.h"
#include "process.h"
#include "processor.h"
#include "queue.h"
#include "randomGenerator.h"
#include "taskScheduler.h"


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

void Event::print()
{
	std::cout << std::fixed << std::setfill(' ') << std::setw(7) << std::setprecision(3)<< getTime() <<": ";
	if (task != nullptr)
	{
		std::cout << " Task"<<std::setfill(' ') << std::setw(3) << task->getPid()<< ": ";
	}
	
	std::cout << getName()<<"\n";
}


void StopSimulation::process()
{
	TaskScheduler::getInstance()->printReports();
	EventList::getInstance()->empty();
	print();
	return;
}

std::string StopSimulation::getName()
{
	return "Simulation stopped";
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
	std::ofstream file;
	file.open("processes.txt", std::ios_base::app);
	task->print(file);
	file.close();
	queueProcess(task);	
	scheduleNextEvent();
	print();
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
	return;
}

std::string NewInteractiveProcess::getName()
{
	return "New interactive process";
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


void NewJob::process()
{
	if (task == nullptr)
		task = createTask();
	queueProcess(task);
	scheduleNextEvent();
	print();
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
	return;
}

std::string NewJob::getName()
{
	return "New job";
}

Process *NewJob::createTask()
{
	double deadline = 30;
	Process *p = Process::createRealTimeTask(10, 35, deadline, ((pid != -1) ? pid:Process::getNewPid()), deadline + time);

	return p;
}

void NewJob::scheduleNextEvent()
{
	if(!renew)
		return;
	NewJob *e = new NewJob(time + task->getPeriod(), new Process(*task), true);
	e->task->setDeadlineTime(e->getTime() + task->getDeadline());
	e->task->incrementJobNumber();
	EventList::getInstance()->insert(e);
}


void TimeOut::process()
{
	TimeOut *nextTimeout = getNextTimeout();
	if (renew)
	{
		nextTimeout->setInterval(interval);
		EventList::getInstance()->insert(nextTimeout);
	}
	print();
	doWork();
	return;
}
void TimeOut::doWork()
{
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
}

TimeOut *TimeOut::getNextTimeout()
{
	return new TimeOut(time+interval);
}

std::string TimeOut::getName()
{
	return "Timeout";
}


double TimeOut::getInterval()
{
	return interval;
}

void TimeOut::setInterval(double inter)
{
	interval = inter;
}

void UsageUpdate::doWork()
{
	Processor::getInstance()->updateUsage(TaskScheduler::getInstance()->isBusy());
}

TimeOut* UsageUpdate::getNextTimeout()
{
	return new UsageUpdate(time+interval);
}

std::string UsageUpdate::getName()
{
	return "Usage update";
}

void FreqUpdate::doWork()
{
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
	return;
}

TimeOut *FreqUpdate::getNextTimeout()
{
	return new FreqUpdate(time+interval);
}

std::string FreqUpdate::getName()
{
	return "Frequency update";
}

void Ready::process()
{
	assert(task != nullptr);
	Queue::getReadyQueue()->add(task);
	Queue::getWaitQueue()->remove(task);
	print();
	TaskScheduler::getInstance()->scheduleTask(eventType, time);
	return;
}

std::string Ready::getName()
{
	return "Task ready";
}


void Waiting::process()
{
	assert(task != nullptr);
	Queue::getWaitQueue()->add(task);
	print();
	Event *e = new Ready(time + task->getCurrentIoTime(), task);
	EventList::getInstance()->insert(e);
	TaskScheduler *scheduler = TaskScheduler::getInstance();
	scheduler->clearRunningTask(task);
	scheduler->scheduleTask(eventType, time);
	return;
}

std::string Waiting::getName()
{
	return "Task waiting";
}


void Terminates::process()
{
	assert(task != nullptr);
	print();
	TaskScheduler *scheduler = TaskScheduler::getInstance();
	scheduler->clearRunningTask(task);
	scheduler->scheduleTask(eventType, time);
	delete task;
	return;
}

std::string Terminates::getName()
{
	return "Task terminates";
}





