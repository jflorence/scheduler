#include "stateSpace.h"

#include <cassert>
#include "policy.h"
#include "transitionMatrix.h"
#include "rewards.h"
#include "action.h"


using namespace Mdp;


StateSpace::StateSpace(int N, std::vector<StateSpaceDimension *> dims) :
	nbOfStates(N),
	dimensions(dims)
{}

StateSpace::~StateSpace()
{
	for (unsigned int i = 0; i < dimensions.size(); i++)
	{
		delete dimensions[i];
	}
}

StateInternal StateSpace::getStateInternal(Processor *proc, Queue *readyQueue, Queue *waitQueue)
{
/*FIXME TODO*/
	StateInternal state = std::vector<int>(dimensions.size());
	for (unsigned int i = 0; i < dimensions.size(); i++)
	{
		StateSpaceDimension *dim = dimensions[i];
		state[dim->getIndex()] = dim->getPosition();
	}
	return state;
}



State StateSpace::getState(Processor *proc, Queue *readyQueue, Queue *waitQueue)
{
	currentState = getStateInternal(proc, readyQueue, waitQueue);
	
	return convertState(currentState);
}





void StateSpace::updateRewards(double currentReward)
{
/*FIXME TODO*/
	return;
}


Action StateSpace::selectAction(Processor *proc, Queue *readyQueue, Queue *waitQueue, double reward)
{
	/*FIXME TODO*/
	return Action::nbOfActions;
}



void StateSpace::setPolicy(Policy *p)
{
	policy = p;
}

void StateSpace::setTransitionMatrix(TransitionMatrix *m)
{
	matrix = m;
}

void StateSpace::setRewards(Rewards *r)
{
	rewards = r;
}

State StateSpace::convertState(StateInternal iState)
{
	int state = 0;
	for (unsigned int i = 0; i < dimensions.size(); i++)
	{
		state += iState[dimensions[i]->getIndex()]; /*I think the index should be the same as i ?*/
		state *= dimensions[i]->getNumberOfPositions();
	}
	return state;
}












StateSpace *StateSpaceBuilder::getStateSpace()
{
	StateSpace *stateSpace = new StateSpace(nbOfStates, dimensions);
	int nbOfActions = ActionSpace::getActionSpace()->size();
	stateSpace->setPolicy(new Policy(nbOfStates));
	stateSpace->setTransitionMatrix(new TransitionMatrix(nbOfStates, nbOfActions));
	stateSpace->setRewards(new Rewards(nbOfStates, nbOfActions));
	return stateSpace;
}

void StateSpaceBuilder::addDimension(StateSpaceDimension *dim)
{
	/*TODO: check that this dimension was not added twice*/
	dim->setIndex(nbOfDimensions++);
	nbOfStates *= dim->getNumberOfPositions();
	assert(nbOfStates > 0); //getNumberOfPositions returns -1 if not defined
	dimensions.push_back(dim);
}




















