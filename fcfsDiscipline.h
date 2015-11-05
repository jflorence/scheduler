#ifndef FCFSDISCIPLINE_H
#define FCFSDISCIPLINE_H

#include "schedulingDiscipline.h"
#include "eventType.h"

class FcfsDiscipline : public SchedulingDiscipline
{
public:
	Process *selectNextTask(Queue *readyQueue, Process *running) override;
	bool preempts(TriggeringEvent trigger) override;
	std::string getName();
};
#endif
