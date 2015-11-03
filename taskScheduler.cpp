#include "taskScheduler.h"
#include "fcfsDiscipline.h"
#include "roundRobinDiscipline.h"
#include "simpleTemperatureModel.h"
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
		scheduler->setTemperatureModel(new SimpleTemperatureModel);
	}
	return scheduler;
}


void TaskScheduler::scheduleTask(TriggeringEvent trigger, double time)
{
	currentTime = time;
	std::cout << currentTime << ": Task scheduler invoked from "<<trigger<<"\n";
	if (trigger != wait && trigger != terminate && !discipline->preempts(trigger) && cpuBusy)
		return;

	EventList *eventList = EventList::getInstance();
	Queue *readyQueue = Queue::getReadyQueue();
	if (discipline->preempts(trigger) && cpuBusy)
	{
		auto it = getBurstEnd();
		if (it != eventList->end())
		{
			double newAow = ((*it)->getTime() - currentTime)*freq;
			runningTask->updateCurrentAow(newAow);
			eventList->remove(it);
		}
		readyQueue->add(runningTask);
	}
	
	updateTemperature();	
	selectTaskAndFreq(readyQueue);
	

	readyQueue->remove(runningTask);
	if (runningTask == nullptr)
	{
		cpuBusy = false;
		std::cout << "Processor sleeping\n";
		return;
	}
	std::cout << "Currently running "<<runningTask->getPid()<<"\n";
	cpuBusy = true;
	double newTime = runningTask->getCurrentCpuAow()/freq;
	newTime += currentTime;
	bool wait = true;
	wait = runningTask->advanceBurst();
	Event *e;
	if (wait)
	{
		e = new Waiting(newTime, runningTask);
	}
	else
	{
		e = new Terminates(newTime, runningTask);
	}
	auto it = eventList->insert(e);
	setBurstEnd(it);
	return;
}

void TaskScheduler::selectTaskAndFreq(Queue *readyQueue)
{
	runningTask = discipline->selectNextTask(readyQueue);
}

void TaskScheduler::updateTemperature()
{
	double runningInterval = currentTime - previousTime;
	energy += power*runningInterval;
	previousTime = currentTime;
	double powerCoeff = (runningTask==nullptr) ? 1.0: runningTask->powerCoeff;
	power = freq*freq*freq*capa*powerCoeff + leakage;

	temperatureModel->updateTemperature(runningInterval, power);
}




void TaskScheduler::setDiscipline(SchedulingDiscipline *disc)
{
	discipline = disc;
	std::cout << "Using scheduling discipline "<<disc->getName()<<"\n";
}

void TaskScheduler::setTemperatureModel(TemperatureModel *model)
{
	temperatureModel = model;
}
void TaskScheduler::setBurstEnd(EventList::iterator it)
{
	burstEnd = it;
}

EventList::iterator TaskScheduler::getBurstEnd()
{
	return burstEnd;
}


