#ifndef CONSERVATIVEGOVERNOR_H
#define CONSERVATIVEGOVERNOR_H

#include "freqGovernor.h"
#include "queue.h"


class ConservativeGovernor
{
public:
	ConservativeGovernor();
	double selectFreq(Queue *readyQueue);
	bool freqChangeEvent(TriggeringEvent trigger);
private:
	double minFreq;
	double maxFreq;
	double currentFreq;

	const double samplingRate{10}; /*FIXME This is pretty much useless here for the moment*/
	const double upThreshold{0.95};
	const double downThreshold{0.75}; /*what value?*/
	const double samplingDownFactor{1.0};
	const double powersaveBias{0.0};
	const double freqStep {0.05};
};

#endif
