#include "priorityDiscipline.h"
#include <algorithm>
#include <vector>
#include "queue.h"
#include "process.h"

Process *PriorityDiscipline::selectNextTask(Queue *readyQueue, Process *running)
{
	updatePriorities(readyQueue, running);

	int highestPriority = -INFINITY;
	Process *candidate = running;
	if (running != nullptr)
		highestPriority = candidate->getPriority();
	for (auto it = readyQueue->begin() ; it != readyQueue->end(); it++)
	{
		if ((*it)->getPriority() > highestPriority)
		{
			candidate = (*it);
			highestPriority = candidate->getPriority();
		}
	}
	return candidate;
}

bool PriorityDiscipline::preempts(TriggeringEvent trigger)
{
	return (trigger == newprocess);
}

std::string PriorityDiscipline::getName()
{
	return "Priority discipline";
}

void PriorityDiscipline::updatePriorities(Queue * readyQueue, Process * running)
{
	std::vector<Process *> ranking(readyQueue->size());
	unsigned int i = 0;
	for (auto it = readyQueue->begin(); it != readyQueue->end(); it++, i++)
	{
		ranking[i] = (*it);
	}
	if (running != nullptr)
		ranking.push_back(running);
	std::sort(ranking.begin(), ranking.end(), getComparator());
	for (unsigned int i = 0; i < ranking.size(); i++)
		ranking[i]->setPriority(ranking.size()-i);
	
}

PriorityDiscipline::ComparatorPointer PriorityDiscipline::getComparator()
{
	return [](Process *a, Process *b){return a->getPriority() > b->getPriority();};
}





