#ifndef REINFORCEMENTSTRATEGY_H
#define REINFORCEMENTSTRATEGY_H

#include "mdpPolicyStrategy.h"

class ReinforcementStrategy : public MdpPolicyStrategy
{
public:
	void updatePolicy(Policy *policy, TransitionMatrix *mat, Rewards *rewards);
};

#endif
