#include "mdpGovernor.h"
#include "mdp/action.h"

#include "processor.h"
#include "queue.h"

MdpGovernor::MdpGovernor()
{
	MdpStateSpaceBuilder builder;
	builder.addDimension(new MdpReadyQueueDimension);
	//builder.addDimension(new MdpWaitQueueDimension);
	//builder.addDimension(new MdpTemperatureDimension);
	//builder.addDimension(new MdpFrequencyDimension);
	//builder.addDimension(new MdpMissRateDimension);
	stateSpace = builder.getStateSpace();
}

MdpGovernor::~MdpGovernor()
{
	delete stateSpace;
}

void MdpGovernor::updateFreq(Processor *proc, Queue *readyQueue)
{
	Queue *waitQueue = Queue::getWaitQueue(); /*FIXME ugly*/
	MdpAction action = stateSpace->selectAction(proc, readyQueue, waitQueue, 0.0);
	/*
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
	*/
	
}


bool MdpGovernor::freqChangeEvent(TriggeringEvent trigger)
{
	if (trigger == ready || trigger == newprocess || trigger == freqUpdate)
		return true;
	return false;
}



std::string MdpGovernor::getName()
{
	return "MDP Governor";
}






































