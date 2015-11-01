#ifndef SCHEDULINGDISCIPLINE_H
#define SCHEDULINGDISCIPLINE_H

#include "eventType.h"

class Process;
class Queue;

class SchedulingDiscipline
{
public:
	virtual Process *selectNextTask(Queue *readyQueue)=0;
	virtual bool preempts(TriggeringEvent)=0;
private:
};

#endif
