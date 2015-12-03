#include "stateSpace.h"

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

StateInternal StateSpace::getStateInternal()
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

State StateSpace::getState()
{
	currentState = getStateInternal();
	
	return convertState(currentState);
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




int StateSpace::getNbOfStates()
{
	return nbOfStates;
}

