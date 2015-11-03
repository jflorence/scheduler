#include "fcfsDiscipline.h"
#include "queue.h"
#include <iostream>

Process *FcfsDiscipline::selectNextTask(Queue *readyQueue)
{
	if (readyQueue->begin() == readyQueue->end())
		std::cout << "fcfs is returning empty\n";
	return (*readyQueue->begin());
}


bool FcfsDiscipline::preempts(TriggeringEvent trigger)
{
	return false;
}


std::string FcfsDiscipline::getName()
{
	return "FCFS";
}



