#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include "eventList.h"
#include "eventType.h"

class Process;
class SchedulingDiscipline;

class TaskScheduler
{
public:
	static TaskScheduler *getInstance();
	void scheduleTask(TriggeringEvent trigger, double currentTime);
	void setDiscipline(SchedulingDiscipline *discipline);
private:
	static TaskScheduler *scheduler;
	Process *runningTask{nullptr};
	double freq{1};
	SchedulingDiscipline *discipline;
	bool cpuBusy{false};
	EventList::iterator burstEnd;
	void setBurstEnd(EventList::iterator it);
	EventList::iterator getBurstEnd();
};

#endif
