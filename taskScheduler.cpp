#include "taskScheduler.h"
#include "fcfsDiscipline.h"
#include "roundRobinDiscipline.h"
#include "freqGovernor.h"
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
		scheduler->setFreqGovernor(nullptr);
	}
	return scheduler;
}

void TaskScheduler::printStatus()
{
	EventList::getInstance()->print();
	Queue::getReadyQueue()->print();
	Queue::getWaitQueue()->print();
}

void TaskScheduler::scheduleTask(TriggeringEvent trigger, double time)
{
	currentTime = time;
	std::cout << currentTime << ": Task scheduler invoked\n";
	Queue *readyQueue = Queue::getReadyQueue();
	EventList *eventList = EventList::getInstance();
	if (trigger != wait && trigger != terminate && !discipline->preempts(trigger) && cpuBusy)
	{
		std::cout << "Currently running "<<runningTask->getPid()<<"\n";
		return;
	}
	if (discipline->preempts(trigger) && cpuBusy)
	{
		Event *ev = getBurstEnd();
		if (ev != nullptr)
		{
			double newAow = (ev->getTime() - currentTime)*freq;
			runningTask->updateCurrentAow(newAow);
			eventList->remove(ev);
			readyQueue->add(runningTask);
			delete ev;
		}
	}

	updateTemperature();

	runningTask = discipline->selectNextTask(readyQueue);

	if (freqGovernor != nullptr && freqGovernor->freqChangeEvent(trigger))
		freq = freqGovernor->selectFreq(readyQueue);

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
	
	setBurstEnd(eventList->insert(e));
	return;
}

void TaskScheduler::selectTaskAndFreq(Queue *readyQueue)
{
	/*not used finally TODO: remove*/
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
void TaskScheduler::setBurstEnd(Event *e)
{
	burstEnd = e;
}

Event *TaskScheduler::getBurstEnd()
{
	return burstEnd;
}

void TaskScheduler::setFreqGovernor(FreqGovernor *gov)
{
	freqGovernor = gov;
}



















