#include "roundRobinDiscipline.h"
#include "queue.h"
#include "eventType.h"
#include <iostream>
#include <cassert>


#include "process.h" //just for testing


RoundRobinDiscipline::RoundRobinDiscipline()
{
}

Process *RoundRobinDiscipline::selectNextTask(Queue *readyQueue, Process * running)
{
	if (readyQueue->isEmpty())
	{
		return running;
	}
	return (*readyQueue->begin());
}


bool RoundRobinDiscipline::preempts(TriggeringEvent trigger)
{
	return (trigger == TriggeringEvent::timeout);
}

std::string RoundRobinDiscipline::getName()
{
	return "Round Robin";
}


