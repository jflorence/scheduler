#ifndef MINGOVERNOR_H
#define MINGOVERNOR_H


#include "freqGovernor.h"

class MinGovernor : public FreqGovernor
{
public:
	MinGovernor();
	void updateFreq(Processor *proc, Queue *readyQueue);
	bool freqChangeEvent(TriggeringEvent trigger);
	std::string getName();
private:
	const double minFreq{1.0}; /*TODO: make this a constant and solve the resulting initialization problem*/
};

#endif
