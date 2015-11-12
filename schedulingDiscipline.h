#ifndef SCHEDULINGDISCIPLINE_H
#define SCHEDULINGDISCIPLINE_H

#include "eventType.h"
#include <string>
#include "visitor.h"

class Process;
class Queue;

class SchedulingDiscipline : public Visitor
{
public:
	virtual Process *selectNextTask(Queue *readyQueue, Process *running)=0;
	virtual bool doesPreempt(Visited *v){return false};
	virtual std::string getName()=0;
	virtual void visit(Event *e);
protected:
	bool preempts{false};
};

#endif
