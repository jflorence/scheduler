#include "noLearning.h"
#include "policy.h"
#include "rewards.h"
#include "transitionMatrix.h"
using namespace Mdp;

NoLearning::NoLearning(Policy *p, Rewards *r, TransitionMatrix *m) : LearningStrategy(p, r, m)
{
}


void NoLearning::initializeModel()
{
	/*TODO FIXME Should we modify this ?*/
	policy->initializeRandomly();
	matrix->initializeRandomly();
}


void NoLearning::updateModel()
{
}




