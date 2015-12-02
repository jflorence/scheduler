#ifndef REINFORCEMENTSTRATEGY_H
#define REINFORCEMENTSTRATEGY_H

#include "learningStrategy.h"

namespace Mdp
{
class ReinforcementStrategy : public LearningStrategy
{
public:
	void update(Policy *policy, TransitionMatrix *mat, Rewards *rewards);
};


}
#endif
