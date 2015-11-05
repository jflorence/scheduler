#ifndef SCHEDULINGDISCIPLINE_H
#define SCHEDULINGDISCIPLINE_H

#include "eventType.h"
#include <string>


class Process;
class Queue;

class SchedulingDiscipline
{
public:
	virtual Process *selectNextTask(Queue *readyQueue, Process *running)=0;
	virtual bool preempts(TriggeringEvent)=0;
	virtual std::string getName()=0;
private:
};

#endif
