#include "minGovernor.h"
#include "queue.h"

MinGovernor::MinGovernor()
{
	minFreq = Processor::getInstance()->getMinFreq();
}

double MinGovernor::selectFreq(Queue * /*readyQueue*/)
{
	return minFreq;
}

bool MinGovernor::freqChangeEvent(TriggeringEvent /*trigger*/)
{
	return true;
}
