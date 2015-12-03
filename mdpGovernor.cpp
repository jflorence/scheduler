#include "mdpGovernor.h"
#include "mdp/action.h"
#include "mdp/mdpModel.h"
#include "mdp/stateSpaceBuilder.h"
#include "mdp/stateSpaceDimension.h"
#include "processor.h"
#include "queue.h"

MdpGovernor::MdpGovernor()
{
	Mdp::StateSpaceBuilder builder;
	builder.addDimension(new Mdp::ReadyQueueDimension);
	//builder.addDimension(new MdpWaitQueueDimension);
	//builder.addDimension(new MdpTemperatureDimension);
	//builder.addDimension(new MdpFrequencyDimension);
	//builder.addDimension(new MdpMissRateDimension);
	Mdp::StateSpace *stateSpace = builder.getStateSpace();
	model = new Mdp::MdpModel(stateSpace);
}

MdpGovernor::~MdpGovernor()
{
	delete model;
}

void MdpGovernor::updateFreq(Processor * /*proc*/, Queue * /*readyQueue*/)
{
	#if 0
	Queue *waitQueue = Queue::getWaitQueue(); /*FIXME ugly*/
	Mdp::Action action = model->selectAction();
#endif
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






































