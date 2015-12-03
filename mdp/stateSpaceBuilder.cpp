#include "stateSpaceBuilder.h"

#include <cassert>
#include "stateSpace.h"
#include "stateSpaceDimension.h"

using namespace Mdp;

StateSpace *StateSpaceBuilder::getStateSpace()
{
	StateSpace *stateSpace = new StateSpace(nbOfStates, dimensions);
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

