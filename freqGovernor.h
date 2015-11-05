#ifndef FREQGOVERNOR_H
#define FREQGOVERNOR_H
#include <string>
#include "eventType.h"
#include "processor.h"

class Queue;

class FreqGovernor
{
public:
	virtual double selectFreq(Queue *readyQueue)=0;
	virtual bool freqChangeEvent(TriggeringEvent trigger)=0;
	virtual std::string getName()=0;
};

#endif
