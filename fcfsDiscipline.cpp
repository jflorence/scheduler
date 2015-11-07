#include "fcfsDiscipline.h"
#include <cassert>
#include <iostream>
#include "queue.h"

Process *FcfsDiscipline::selectNextTask(Queue *readyQueue, Process * running)
{
	if (readyQueue->isEmpty())
	{
		assert(running == nullptr);
		return running; /*For a fcfs, this should be nullptr*/
	}
	return (*readyQueue->begin());
}


bool FcfsDiscipline::preempts(TriggeringEvent /*trigger*/)
{
	return false;
}


std::string FcfsDiscipline::getName()
{
	return "FCFS";
}



