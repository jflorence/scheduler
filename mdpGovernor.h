#ifndef MDPGOVERNOR_H
#define MDPGOVERNOR_H

#include "freqGovernor.h"
#include "mdpStateSpace.h"




class MdpGovernor : public FreqGovernor
{
public:
	MdpGovernor();
	virtual ~MdpGovernor();
	virtual void updateFreq(Processor *proc, Queue *readyQueue);
	virtual bool freqChangeEvent(TriggeringEvent trigger);
	virtual std::string getName();
private:
	MdpStateSpace *stateSpace;
	/*TODO keep track of the MdpAction history*/
};




#endif
