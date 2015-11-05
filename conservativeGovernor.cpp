#include "conservativeGovernor.h"
#include "processor.h"
#include <algorithm>
ConservativeGovernor::ConservativeGovernor() : 
	maxFreq(Processor::getInstance()->getMaxFreq()), minFreq(Processor::getInstance()->getMinFreq())
{
	currentFreq = minFreq;
}

double ConservativeGovernor::selectFreq(Queue * /*readyQueue*/)
{
	/*TODO not finished*/
	Processor *proc = Processor::getInstance();
	if (proc->getUsage() > upThreshold)
	{
		currentFreq = std::min(maxFreq, currentFreq + freqStep*maxFreq);
	}
	else if (proc->getUsage() < downThreshold)
	{
		currentFreq = std::max(minFreq, currentFreq - freqStep*maxFreq);
	}
	return currentFreq;
}

bool ConservativeGovernor::freqChangeEvent(TriggeringEvent trigger)
{
	return (trigger == freqUpdate);
}

std::string ConservativeGovernor::getName()
{
	return "ConservativeGovernor";
}
