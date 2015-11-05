#include "roundRobinDiscipline.h"
#include "queue.h"
#include "eventType.h"
#include <iostream>
#include <cassert>


#include "process.h" //just for testing


RoundRobinDiscipline::RoundRobinDiscipline()
{
}

Process *RoundRobinDiscipline::selectNextTask(Queue *readyQueue, Process * /*running*/)
{
	if (readyQueue->isEmpty())
	{
		currentProcess = nullptr;
		return nullptr;
	}
	if (readyQueue->size() == 1)
	{
		currentProcess = (*readyQueue->begin());
		return currentProcess;
	}
	for (auto it = readyQueue->begin(); it != readyQueue->end(); it++)
	{
		if ((*it) == currentProcess)
		{
			it++;
			if(it == readyQueue->end())
			{
				currentProcess = (*readyQueue->begin());
				return currentProcess;
			}
			currentProcess = (*it);
			return currentProcess;
		}
	}
	currentProcess = *(readyQueue->begin());
	return currentProcess;
}


bool RoundRobinDiscipline::preempts(TriggeringEvent trigger)
{
	return (trigger == TriggeringEvent::timeout);
}

std::string RoundRobinDiscipline::getName()
{
	return "Round Robin";
}


