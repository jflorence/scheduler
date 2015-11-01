#ifndef FCFSDISCIPLINE_H
#define FCFSDISCIPLINE_H

#include "schedulingDiscipline.h"
#include "eventType.h"

class FcfsDiscipline : public SchedulingDiscipline
{
public:
	Process *selectNextTask(Queue *readyQueue) override;
	bool preempts(TriggeringEvent trigger) override;
};
#endif
