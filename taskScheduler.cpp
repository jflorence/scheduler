#include "taskScheduler.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <utility>

#include "conservativeGovernor.h"
#include "edfDiscipline.h"
#include "event.h"
#include "eventList.h"
#include "eventType.h"
#include "fcfsDiscipline.h"
#include "maxGovernor.h"
#include "minGovernor.h"
#include "process.h"
#include "queue.h"
#include "rmsDiscipline.h"
#include "roundRobinDiscipline.h"
#include "simpleTemperatureModel.h"

TaskScheduler *TaskScheduler::scheduler = nullptr;

TaskScheduler *TaskScheduler::getInstance()
{
	if (scheduler == nullptr)
	{
		scheduler = new TaskScheduler();
		//scheduler->setDiscipline(new FcfsDiscipline);
		//scheduler->setDiscipline(new RoundRobinDiscipline);
		//scheduler->setDiscipline(new PriorityDiscipline);
		//scheduler->setDiscipline(new RmsDiscipline);
		scheduler->setDiscipline(new EdfDiscipline);
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
	Queue *readyQueue = Queue::getReadyQueue();
	EventList *eventList = EventList::getInstance();
	if (trigger == terminate || trigger == wait)
	{
		runningTask = nullptr; /*Do we need this line?*/
	}
	if (trigger != wait && trigger != terminate && !discipline->preempts(trigger) && cpuBusy)
	{
		return;
	}
	printInvocation();
	
	updateTemperature();
		
	Process *nextTask = discipline->selectNextTask(readyQueue, runningTask);
	
	if (nextTask == runningTask && runningTask != nullptr)
	{
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

	readyQueue->remove(nextTask);
	runningTask = nextTask;

	if (freqGovernor != nullptr && freqGovernor->freqChangeEvent(trigger))
	{
		freq = freqGovernor->selectFreq(readyQueue);
	}

	cpuBusy = (runningTask != nullptr);
	if (cpuBusy)
	{
		double newTime = currentTime + runningTask->getCurrentCpuAow()/freq;
		bool wait = runningTask->advanceBurst();
		Event *e = wait ? (Event*) new Waiting(newTime, runningTask) : (Event*) new Terminates(newTime, runningTask);
	
		setBurstEnd(eventList->insert(e));
	}
	printRunningProcess();
	return;
}

void TaskScheduler::printInvocation()
{
	std::cout << "\033[34m"<< "    Scheduler invoked. Ready queue contains " 
		<< Queue::getReadyQueue()->getDisplay() << "\033[0m" <<"\n";
}

void TaskScheduler::printRunningProcess()
{
	if (cpuBusy)
	{
		std::cout << "\033[1;34m"<<"    Currently running process number "<<runningTask->getPid();
		if (runningTask->isRealTime())
			std::cout << ":"<< runningTask->getJobNumber();
	
		std::cout << "\033[0m"<<"\n";
	}
	else
	{
		std::cout << "\033[1;34m" << "    Processor sleeping"<<"\033[0m"<<"\n";
	}
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











