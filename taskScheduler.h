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
	void setTemperatureModel(TemperatureModel *model);
	void setFreqGovernor(FreqGovernor *gov);
	bool isBusy();
	void printReports();
private:
	
	void updateTemperature();
	void printStatus();
	void printRunningProcess();
	void printInvocation();
	
	SchedulingDiscipline *discipline{nullptr};
	TemperatureModel *temperatureModel{nullptr};
	FreqGovernor *freqGovernor{nullptr};
	Process *runningTask{nullptr};
	double freq{1};
	bool cpuBusy{false};
	Event *burstEnd;
	void setBurstEnd(Event *e);
	Event *getBurstEnd();
	double previousTime{0.0};
	double currentTime{0.0};
	double energy{0.0};
	double power{0.0};
	double capa{1.0};
	double leakage{1.0};
	
};

#endif
