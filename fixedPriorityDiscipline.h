#ifndef FIXEDPRIORITYDISCIPLINE_H
#define FIXEDPRIORITYDISCIPLINE_H

#include "priorityDiscipline.h"

class FixedPriorityDiscipline : public PriorityDiscipline
{
public:
	std::string getName();
	void updatePriorities(Queue *readyQueue, Process *running) override;
};

#endif
