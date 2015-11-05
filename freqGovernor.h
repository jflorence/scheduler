#ifndef FREQGOVERNOR_H
#define FREQGOVERNOR_H

#include "eventType.h"
#include "processor.h"

class Queue;

class FreqGovernor
{
public:
	virtual double selectFreq(Queue *readyQueue)=0;
	virtual bool freqChangeEvent(TriggeringEvent trigger)=0;
};

#endif
