#ifndef NOLEARNING_H
#define NOLEARNING_H

#include "learningStrategy.h"

namespace Mdp
{

class NoLearning : public LearningStrategy
{
public:
	NoLearning(Policy *policy, Rewards *rewards, TransitionMatrix *matrix);
	void updateModel();
	void initializeModel();
private:
};


}
#endif
