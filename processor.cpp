#include "processor.h"

Processor *Processor::proc = nullptr;


Processor *Processor::getInstance()
{
	if (proc == nullptr)
		proc = new Processor;
	return proc;
}

double Processor::getMaxFreq()
{
	return maxFreq;
}

double Processor::getMinFreq()
{
	return minFreq;
}

double Processor::getUsage()
{
	return usage;
}

void Processor::updateUsage(bool busy)
{/*exponential average. Is that the best average to use?*/
	usage = (1.0 - alpha)*usage + alpha*(busy?1.0:0.0);
}
