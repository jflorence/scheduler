#include "minGovernor.h"
#include "queue.h"
#include "system.h"
MinGovernor::MinGovernor() : minFreq(System::getInstance()->getProc()->getMinFreq())
{
}

void MinGovernor::updateFreq(Processor *proc, Queue * /*readyQueue*/)
{
	proc->setFreq(minFreq);
}

bool MinGovernor::freqChangeEvent(TriggeringEvent /*trigger*/)
{
	return true;
}

std::string MinGovernor::getName()
{
	return "MinGovernor";
}



