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
#include "log.h"
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
		scheduler->setDiscipline(new RoundRobinDiscipline);
		//scheduler->setDiscipline(new PriorityDiscipline);
		//scheduler->setDiscipline(new RmsDiscipline);
		//scheduler->setDiscipline(new EdfDiscipline);
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

	if (freqGovernor != nullptr && freqGovernor->freqChangeEvent(trigger))
	{
		freq = freqGovernor->selectFreq(readyQueue);
	}
	if (trigger != wait && trigger != terminate && !discipline->preempts(trigger) && cpuBusy)
	{
		return;
	}
	printInvocation();
	
	updateTemperature();

	if (trigger == terminate || trigger == wait)
	{
		runningTask = nullptr;
	}
	Process *nextTask = discipline->selectNextTask(readyQueue, runningTask);
	
	if (nextTask == runningTask && runningTask != nullptr)
	{
		return;
	}
	if (discipline->preempts(trigger))
	{
		putRunningTaskBackToReadyQueue();
	}

	runningTask = nextTask;
	readyQueue->remove(nextTask);


	cpuBusy = (runningTask != nullptr);
	scheduleEndOfBurst();
	printRunningProcess();
	return;
}

void TaskScheduler::scheduleEndOfBurst()
{
	EventList *eventList = EventList::getInstance();
	if (!cpuBusy)
		return;

	double newTime = currentTime + runningTask->getCurrentCpuAow()/freq;
	bool wait = runningTask->advanceBurst();
	Event *e = wait ? (Event*) new Waiting(newTime, runningTask) : (Event*) new Terminates(newTime, runningTask);

	setBurstEnd(eventList->insert(e));
}

void TaskScheduler::putRunningTaskBackToReadyQueue()
{
	EventList *eventList = EventList::getInstance();
	Queue *readyQueue = Queue::getReadyQueue();
	if (!cpuBusy)
		return;
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

void TaskScheduler::printInvocation()
{
	std::cout << "\033[34m"<< "    Scheduler invoked. Ready queue contains " 
		<< Queue::getReadyQueue()->getDisplay() << "\033[0m" <<"\n";
}

void TaskScheduler::printRunningProcess()
{
	Log log;
	if (cpuBusy)
	{
		log << Log::Color::blue<<"    Currently running process number "<<runningTask->getPid();
		
		if (runningTask->isRealTime())
			log << ":"<< runningTask->getJobNumber();
	
		log << Log::Color::normal << "\n";
	}
	else
	{
		log << Log::Color::blue << "    Processor sleeping" << Log::Color::normal << "\n";
	}
}

void TaskScheduler::updateTemperature()
{
	double runningInterval = currentTime - previousTime;
	energy += power*runningInterval;
	previousTime = currentTime;
	double powerCoeff = (runningTask==nullptr) ? 0.0: runningTask->powerCoeff;
	power = freq*freq*freq*capa*powerCoeff + leakage;

	temperatureModel->updateTemperature(runningInterval, power);
}




void TaskScheduler::setDiscipline(SchedulingDiscipline *disc)
{
	discipline = disc;
	Log log;
	log << Log::Color::green << "Using scheduling discipline " << disc->getName() << Log::Color::normal << "\n";
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
	Log log;
	log << Log::Color::green << "Using frequency governor "<<gov->getName()<< Log::Color::normal <<"\n";
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











