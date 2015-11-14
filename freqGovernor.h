#ifndef FREQGOVERNOR_H
#define FREQGOVERNOR_H
#include <string>
#include "eventType.h"
#include "processor.h"

class Queue;
class Processor;

class FreqGovernor
{
public:
	virtual void updateFreq(Processor *proc, Queue *readyQueue)=0;
	virtual bool freqChangeEvent(TriggeringEvent trigger)=0;
	virtual std::string getName()=0;
};

#endif
