#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include "eventList.h"
#include "eventType.h"

class Process;
class SchedulingDiscipline;
class TemperatureModel;
class Queue;
class Event;
class FreqGovernor;
class TaskScheduler
{
public:
	static TaskScheduler *getInstance();
private:	
	static TaskScheduler *scheduler;
public:
	void scheduleTask(TriggeringEvent trigger, double currentTime);
	void setDiscipline(SchedulingDiscipline *discipline);
	void setFreqGovernor(FreqGovernor *gov);
	void printReports();
	void scheduleEndOfBurst(Process *runningTask);
	void clearRunningTask(Process *p);
private:
	
	void updateTemperature();
	void printStatus();
	void printRunningProcess(Process *runningTask);
	void printInvocation();
	void putRunningTaskBackToReadyQueue(Process *task);
	
	SchedulingDiscipline *discipline{nullptr};
	FreqGovernor *freqGovernor{nullptr};
	
	Process *runningTask{nullptr};
	Event *burstEnd;
	void setBurstEnd(Event *e);
	Event *getBurstEnd();
	
	double previousTime{0.0};
	double currentTime{0.0};
	
};

#endif
