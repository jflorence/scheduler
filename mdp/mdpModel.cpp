#include "mdpModel.h"
#include "stateSpace.h"
#include "transitionMatrix.h"
#include "rewards.h"
#include "policy.h"
#include "learningStrategy.h"
#include "noLearning.h"


using namespace Mdp;

MdpModel::MdpModel(StateSpace *space)
{
	stateSpace = space;
	int s = stateSpace->getNbOfStates();
	int a = ActionSpace::getActionSpace()->size();
	matrix = new TransitionMatrix(s, a);
	rewards = new Rewards(s, a);
	policy = new Policy(s, a);
	learningStrategy = new NoLearning(policy, rewards, matrix);
}

MdpModel::~MdpModel()
{
	delete learningStrategy;
	delete policy;
	delete rewards;
	delete matrix;
}


Action MdpModel::selectAction()
{
	return policy->getAction(stateSpace->getState());
}





