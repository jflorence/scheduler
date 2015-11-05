#include "priorityDiscipline.h"

#include "queue.h"

Process *PriorityDiscipline::selectNextTask(Queue *readyQueue, Process *running)
{
	Process *candidate = running;
	int highestPriority = candidate->getPriority();
	for (auto it = readyQueue.begin() ; it != readyQueue.end(); it++)
	{
		if (*it)->getPriority > highestPriority)
		{
			candidate = (*it);
			highestPriority = candidate->getPriority;
		}
	}
	return nullptr;
}

bool PriorityDiscipline::preempts(TriggeringEvent trigger)
{
	return (trigger == newprocess);
}

std::string PriorityDiscipline::getName()
{
	return "Priority discipline";
}


