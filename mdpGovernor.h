#ifndef MDPGOVERNOR_H
#define MDPGOVERNOR_H

#include "freqGovernor.h"


class MdpGovernor : public FreqGovernor
{
public:
	virtual void updateFreq(Processor *proc, Queue *readyQueue);
	virtual bool freqChangeEvent(TriggeringEvent trigger);
	virtual std::string getName();
};




#endif
