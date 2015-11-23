#include "mdpGovernor.h"

#include "processor.h"
#include "queue.h"



void MdpGovernor::updateFreq(Processor *Proc, Queue *readyQueue)
{
	MdpState state = getState(proc, readyQueue);
	MdpAction action = mdp.getAction(state);
	double freq = 1.0;
	switch (action)
	{
	case MdpAcion::minFreq:
		proc->setFreq(proc->getMinFreq());
		break;
	case MdpAction::maxFreq:
		proc->setFreq(proc->getMaxFreq());
		break;
	case MdpAction::off:
		break;
	default:
		break;
	}

}


bool freqChangeEvent(TriggeringEvent trigger)
{
	if (trigger == ready || trigger == newprocess || trigger == freqUpdate)
		return true;
	return false;
}



std::string MdpGovernor::getName()
{
	return "MDP Governor";
}



MdpState MdpGovernor::getState(Processor *proc, Queue *readyQueue)
{
	return 0; /*FIXME*/
}



































