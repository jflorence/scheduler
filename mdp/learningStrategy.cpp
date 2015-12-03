#include "learningStrategy.h"

#include "policy.h"
#include "rewards.h"
#include "transitionMatrix.h"


using namespace Mdp;

LearningStrategy::LearningStrategy(Policy *p, Rewards *r, TransitionMatrix *m) :
	policy(p), rewards(r), matrix(m)
{
}

LearningStrategy::~LearningStrategy()
{
}


