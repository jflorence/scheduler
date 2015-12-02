#include "mdpStateSpace.h"

#include <cassert>
#include "mdpPolicy.h"
#include "mdpTransitionMatrix.h"
#include "mdpRewards.h"
#include "mdpAction.h"
#include "processor.h"
#include "queue.h"


MdpStateSpace::MdpStateSpace(int N, std::vector<MdpStateSpaceDimension *> dims) :
	nbOfStates(N),
	dimensions(dims)
{}

MdpStateSpace::~MdpStateSpace()
{
	for (unsigned int i = 0; i < dimensions.size(); i++)
	{
		delete dimensions[i];
	}
}

MdpStateInternal MdpStateSpace::getStateInternal(Processor *proc, Queue *readyQueue, Queue *waitQueue)
{
/*FIXME TODO*/
	MdpStateInternal state = std::vector<int>(dimensions.size());
	for (unsigned int i = 0; i < dimensions.size(); i++)
	{
		MdpStateSpaceDimension *dim = dimensions[i];
		state[dim->getIndex()] = dim->getPosition();
	}
	return state;
}



MdpState MdpStateSpace::getState(Processor *proc, Queue *readyQueue, Queue *waitQueue)
{
	currentState = getStateInternal(proc, readyQueue, waitQueue);
	
	return convertState(currentState);
}





void MdpStateSpace::updateRewards(double currentReward)
{
/*FIXME TODO*/
	return;
}


MdpAction MdpStateSpace::selectAction(Processor *proc, Queue *readyQueue, Queue *waitQueue, double reward)
{
	/*FIXME TODO*/
	return MdpAction::nbOfActions;
}



void MdpStateSpace::setPolicy(MdpPolicy *p)
{
	policy = p;
}

void MdpStateSpace::setTransitionMatrix(MdpTransitionMatrix *m)
{
	matrix = m;
}

void MdpStateSpace::setRewards(MdpRewards *r)
{
	rewards = r;
}

MdpState MdpStateSpace::convertState(MdpStateInternal iState)
{
	int state = 0;
	for (unsigned int i = 0; i < dimensions.size(); i++)
	{
		state += iState[dimensions[i]->getIndex()]; /*I think the index should be the same as i ?*/
		state *= dimensions[i]->getNumberOfPositions();
	}
	return state;
}












MdpStateSpace *MdpStateSpaceBuilder::getStateSpace()
{
	MdpStateSpace *stateSpace = new MdpStateSpace(nbOfStates, dimensions);
	int nbOfActions = MdpActionSpace::getActionSpace()->size();
	stateSpace->setPolicy(new MdpPolicy(nbOfStates));
	stateSpace->setTransitionMatrix(new MdpTransitionMatrix(nbOfStates, nbOfActions));
	stateSpace->setRewards(new MdpRewards(nbOfStates, nbOfActions));
	return stateSpace;
}

void MdpStateSpaceBuilder::addDimension(MdpStateSpaceDimension *dim)
{
	/*TODO: check that this dimension was not added twice*/
	dim->setIndex(nbOfDimensions++);
	nbOfStates *= dim->getNumberOfPositions();
	assert(nbOfStates > 0); //getNumberOfPositions returns -1 if not defined
	dimensions.push_back(dim);
}




















