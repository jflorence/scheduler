#ifndef MDPSTATESPACE_H
#define MDPSTATESPACE_H

#include <vector>
#include "stateSpaceDimension.h"
#include "action.h"
#include "state.h"
class Queue;
class Processor;


namespace Mdp
{

typedef std::vector<int> StateInternal;


class StateSpace
{
	friend class StateSpaceBuilder;
public:
	~StateSpace();
	int getNbOfStates();
	State getState();
	StateInternal getStateInternal();
private:
	/*state space has to be constructed with the builder*/
	StateSpace(int nbOfStates, std::vector<StateSpaceDimension *> dimensions);
	State convertState(StateInternal);

	int nbOfStates;
	std::vector<StateSpaceDimension *> dimensions;
	StateInternal currentState;
};





}




#endif
