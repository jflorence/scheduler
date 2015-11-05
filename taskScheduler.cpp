#include "taskScheduler.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <utility>

#include "conservativeGovernor.h"
#include "event.h"
#include "eventList.h"
#include "eventType.h"
#include "fcfsDiscipline.h"
#include "maxGovernor.h"
#include "minGovernor.h"
#include "process.h"
#include "queue.h"
#include "roundRobinDiscipline.h"
#include "simpleTemperatureModel.h"

TaskScheduler *TaskScheduler::scheduler = nullptr;

TaskScheduler *TaskScheduler::getInstance()
{
	if (scheduler == nullptr)
	{
		scheduler = new TaskScheduler();
		//scheduler->setDiscipline(new FcfsDiscipline);
		scheduler->setDiscipline(new RoundRobinDiscipline);
		scheduler->setTemperatureModel(new SimpleTemperatureModel);
		//scheduler->setFreqGovernor(new MinGovernor);
		scheduler->setFreqGovernor(new ConservativeGovernor);
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
	//std::cout << currentTime << ": Task scheduler invoked\n";
	Queue *readyQueue = Queue::getReadyQueue();
	EventList *eventList = EventList::getInstance();
	if (trigger != wait && trigger != terminate && !discipline->preempts(trigger) && cpuBusy)
	{
		return;
	}

	std::cout << "\033[34m"<< "    Scheduler invoked. Ready queue contains " << readyQueue->getDisplay() << "\033[0m" <<"\n";

	if (discipline->preempts(trigger) && cpuBusy)
	{
		Event *ev = getBurstEnd();
		/*FIXME If a cpuBurst ends after the end of simulation, ev will be nullptr, and the cpu will be put to sleep.*/
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
	
	runningTask = discipline->selectNextTask(readyQueue, runningTask);
	if (freqGovernor != nullptr)
	{
		if (freqGovernor->freqChangeEvent(trigger))
		{
			freq = freqGovernor->selectFreq(readyQueue);
		}
	}

	readyQueue->remove(runningTask);
	if (runningTask == nullptr)
	{
		cpuBusy = false;
		std::cout << "\033[1;34m" << "    Processor sleeping"<<"\033[0m"<<"\n";
		return;
	}
	std::cout << "\033[1;34m"<<"    Currently running process number "<<runningTask->getPid()<< "\033[0m"<<"\n";
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
	std::cout <<"\033[1;32m"<< "Using scheduling discipline "<<disc->getName()<<"\033[0m"<<"\n";
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
	std::cout <<"\033[1;32m"<< "Using frequency governor "<<gov->getName()<<"\033[0m"<<"\n";
}



bool TaskScheduler::isBusy()
{
	return cpuBusy;
}



void TaskScheduler::printReports()
{
	std::ofstream file;
	file.open("reports.txt", std::ios_base::app);
	std::vector<std::pair<double, double>> tempHist = temperatureModel->getTemperatureHistory();
	file << "temperature report:\n";
	for (unsigned int i = 0; i < tempHist.size(); i++)
	{
		file << tempHist[i].first << ": " << tempHist[i].second << "\n";	
	}
	file << "\n";
	file.close();
}











