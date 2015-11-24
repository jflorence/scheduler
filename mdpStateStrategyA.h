#ifndef MDPSTATESTRATEGYA_H
#define MDPSTATESTRATEGYA_H

#include "mdpStateStrategy.h"



class MdpStateStrategyA : public MdpStateStrategy
{
public:
	MdpState getState(Processor *proc, Queue *readyQueue, Queue *waitQueue);

};


#endif
