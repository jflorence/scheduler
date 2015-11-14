#include "maxGovernor.h"
#include "queue.h"
#include "processor.h"
#include "system.h"
MaxGovernor::MaxGovernor() : maxFreq(System::getInstance()->getProc()->getMaxFreq())
{
}

void MaxGovernor::updateFreq(Processor *proc, Queue * /*readyQueue*/)
{
	proc->setFreq(maxFreq);
}

bool MaxGovernor::freqChangeEvent(TriggeringEvent /*trigger*/)
{
	return true;
}

std::string MaxGovernor::getName()
{
	return "MaxGovernor";
}
