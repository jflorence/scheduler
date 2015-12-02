#ifndef REINFORCEMENTSTRATEGY_H
#define REINFORCEMENTSTRATEGY_H

#include "learningStrategy.h"

class ReinforcementStrategy : public MdpLearningStrategy
{
public:
	void update(Policy *policy, TransitionMatrix *mat, Rewards *rewards);
};

#endif
