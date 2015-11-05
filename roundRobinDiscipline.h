#ifndef ROUNDROBINDISCIPLINE_H
#define ROUNDROBINDISCIPLINE_H

#include "schedulingDiscipline.h"
#include "queue.h"
#include "eventType.h"

class Process;

class RoundRobinDiscipline : public SchedulingDiscipline
{
public:
	RoundRobinDiscipline();
	Process *selectNextTask(Queue *readyQueue, Process *running);
	bool preempts(TriggeringEvent trigger);
	std::string getName();
private:
	Process *currentProcess{nullptr};
};


#endif
