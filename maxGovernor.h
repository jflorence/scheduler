#ifndef MAXGOVERNOR_H
#define MAXGOVERNOR_H

#include "freqGovernor.h"

class MaxGovernor : public FreqGovernor
{
public:
	MaxGovernor();
	double selectFreq(Queue *readyQueue);
	bool freqChangeEvent(TriggeringEvent trigger);
private:
	double maxFreq{2.0}; /*TODO make this a const and solve the resulting initialization problem*/
};

#endif
