#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include "eventList.h"
#include "eventType.h"
class Process;
class SchedulingDiscipline;
class TemperatureModel;

class TaskScheduler
{
public:
	static TaskScheduler *getInstance();
	void scheduleTask(TriggeringEvent trigger, double currentTime);
	void setDiscipline(SchedulingDiscipline *discipline);
	void setTemperatureModel(TemperatureModel *model);
private:
	static TaskScheduler *scheduler;
	Process *runningTask{nullptr};
	double freq{1};
	SchedulingDiscipline *discipline{nullptr};
	bool cpuBusy{false};
	EventList::iterator burstEnd;
	void setBurstEnd(EventList::iterator it);
	EventList::iterator getBurstEnd();
	double previousTime{0.0};
	double energy{0.0};
	double power{0.0};
	double capa{1.0};
	double leakage{1.0};
	TemperatureModel *temperatureModel{nullptr};
};

#endif
