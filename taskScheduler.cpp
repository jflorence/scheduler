#include "taskScheduler.h"
#include "fcfsDiscipline.h"
#include "roundRobinDiscipline.h"
#include "eventList.h"
#include "queue.h"
#include "process.h"
#include "event.h"
#include <iostream>
#include <cassert>
#include "eventType.h"


TaskScheduler *TaskScheduler::scheduler = nullptr;

TaskScheduler *TaskScheduler::getInstance()
{
	if (scheduler == nullptr)
	{
		scheduler = new TaskScheduler();
		//scheduler->setDiscipline(new FcfsDiscipline);
		scheduler->setDiscipline(new RoundRobinDiscipline);
	}
	return scheduler;
}


void TaskScheduler::scheduleTask(TriggeringEvent trigger, double currentTime)
{
	std::cout << currentTime << ": Task scheduler invoked from "<<trigger<<"\n";
	if (trigger != wait && trigger != terminate && !discipline->preempts(trigger) && cpuBusy)
		return;
	assert((cpuBusy && runningTask != nullptr) || (!cpuBusy && runningTask == nullptr));
	EventList *eventList = EventList::getInstance();
	Queue *readyQueue = Queue::getReadyQueue();
	Event *e;
	if (discipline->preempts(trigger) && cpuBusy)
	{
		auto it = getBurstEnd();
		double newAow = ((*it)->getTime() - currentTime)*freq;
		runningTask->updateCurrentAow(newAow);
		eventList->remove(it);
		readyQueue->add(runningTask);
	}
	runningTask = discipline->selectNextTask(readyQueue);/*this function should also update the frequency*/
	readyQueue->remove(runningTask);
	if (runningTask == nullptr)
	{
		cpuBusy = false;
		return;
	}
	cpuBusy = true;
	double time = runningTask->getCurrentCpuAow()/freq;
	time += currentTime;
	bool wait = true;
	wait = runningTask->advanceBurst();
	if (wait)
	{
		e = new Waiting(time, runningTask);
	}
	else
	{
		e = new Terminates(time, runningTask);
	}
	auto it = eventList->insert(e);
	setBurstEnd(it);
	return;
}





void TaskScheduler::setDiscipline(SchedulingDiscipline *disc)
{
	discipline = disc;
}


void TaskScheduler::setBurstEnd(EventList::iterator it)
{
	burstEnd = it;
}

EventList::iterator TaskScheduler::getBurstEnd()
{
	return burstEnd;
}


