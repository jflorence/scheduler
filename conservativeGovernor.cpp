#include "conservativeGovernor.h"
#include "processor.h"

ConservativeGovernor::ConservativeGovernor() : 
	maxFreq(Processor::getInstance()->getMaxFreq()), minFreq(Processor::getInstance()->getMinFreq())
{
}

double ConservativeGovernor::selectFreq(Queue *readyQueue)
{
	/*TODO...*/
	return maxFreq;
}

bool ConservativeGovernor::freqChangeEvent(TriggeringEvent trigger)
{
	return (trigger == freqUpdate);
}

std::string ConservativeGovernor::getName()
{
	return "ConservativeGovernor";
}
