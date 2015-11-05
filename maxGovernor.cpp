#include "maxGovernor.h"
#include "queue.h"
#include "processor.h"

MaxGovernor::MaxGovernor() : maxFreq(Processor::getInstance()->getMaxFreq())
{
}

double MaxGovernor::selectFreq(Queue * /*readyQueue*/)
{
	return maxFreq;
}

bool MaxGovernor::freqChangeEvent(TriggeringEvent /*trigger*/)
{
	return true;
}

std::string MaxGovernor::getName()
{
	return "MaxGovernor";
}
