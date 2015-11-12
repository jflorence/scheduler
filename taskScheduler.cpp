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
#include "system.h"

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

void clearRunningTask(Process *p)
{
	Processor *proc = System::getInstance()->getProc();
	assert(p == proc->getRunningTask());
	proc->setRunning(nullptr);
	proc->setBusy(false);
}

void TaskScheduler::scheduleTask(Visited *e, double time)
{
	bool preempts = discipline->doesPreempt(e);
	currentTime = time;
	Queue *readyQueue = Queue::getReadyQueue();
	Processor *proc = System::getInstance()->getProc();
	
	printInvocation();
	
	if (freqGovernor != nullptr && freqGovernor->freqChangeEvent(trigger))
	{
		proc->setFreq(freqGovernor->selectFreq(readyQueue));
	}
	if (!preempts && proc->isBusy())
	{
		return;
	}
	

	Process *nextTask = discipline->selectNextTask(readyQueue, proc->getRunningTask());
	
	if (proc->isRunning(nextTask) /*&& runningTask != nullptr*/)
	{
		return;
	}
	if (discipline->preempts(trigger)) 
	{
		putRunningTaskBackToReadyQueue(proc->getRunningTask());
	}

	proc->setRunning(nextTask);
	readyQueue->remove(nextTask);


	proc->setBusy(nextTask != nullptr);
	scheduleEndOfBurst(nextTask);
	printRunningProcess(nextTask);
	return;
}

void TaskScheduler::scheduleEndOfBurst(Process *runningTask)
{
	Processor *proc = Processor::getInstance();
	EventList *eventList = EventList::getInstance();
	if (!cpuBusy)
		return;

	double newTime = currentTime + runningTask->getCurrentCpuAow()/proc->getFreq();
	bool wait = runningTask->advanceBurst();
	Event *e = wait ? (Event*) new Waiting(newTime, runningTask) : (Event*) new Terminates(newTime, runningTask);

	setBurstEnd(eventList->insert(e));
}

void TaskScheduler::putRunningTaskBackToReadyQueue(Process *runningTask)
{
	Processor *proc = Processor::getInstance();
	EventList *eventList = EventList::getInstance();
	Queue *readyQueue = Queue::getReadyQueue();
	if (!proc->isBusy())
		return;
	Event *ev = getBurstEnd();
	if (ev != nullptr)
	{
		double newAow = (ev->getTime() - currentTime)*proc->getFreq();
		runningTask->updateCurrentAow(newAow);
		eventList->remove(ev);
		readyQueue->add(runningTask);
		delete ev;
	}
}

void TaskScheduler::printInvocation()
{
	Log log;
	log << Log::Color::lightBlue << "    Scheduler invoked. Ready queue contains " 
		<< Queue::getReadyQueue()->getDisplay() << Log::Color::normal <<"\n";
}

void TaskScheduler::printRunningProcess(Process *runningTask)
{
	Log log;
	if (runningTask != nullptr)
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
	double timeInterval = currentTime - previousTime;
	previousTime = currentTime;
	Processor::getInstance()->updateTemperature(timeInterval);
}




void TaskScheduler::setDiscipline(SchedulingDiscipline *disc)
{
	discipline = disc;
	Log log;
	log << Log::Color::green << "Using scheduling discipline " << disc->getName() << Log::Color::normal << "\n";
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




void TaskScheduler::printReports()
{
	Processor::getInstance()->printTemperatureReport();
}











