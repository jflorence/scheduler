#ifndef PRIORITYDISCIPLINE_H
#define PRIORITYDISCIPLINE_H

#include "schedulingDiscipline.h"

class PriorityDiscipline : public SchedulingDiscipline
{
public:
	typedef bool (*ComparatorPointer)(Process *, Process *);
	Process *selectNextTask(Queue *readyQueue, Process *running);
	virtual bool doesPreempt(Visited *v);
	virtual std::string getName();
protected:
	virtual void updatePriorities(Queue *readyQueue, Process *running);
	virtual  ComparatorPointer getComparator();
};

#endif
