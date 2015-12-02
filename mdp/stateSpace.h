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

class Policy;
class TransitionMatrix;
class Rewards;


typedef std::vector<int> StateInternal;



class StateSpace
{
	friend class StateSpaceBuilder;
public:

	void updateRewards(double currentReward);
	Action selectAction(Processor *proc, Queue *readyQueue, Queue *waitQueue, double reward);
	~StateSpace();

private:
	/*state space has to be constructed with the builder*/
	StateSpace(int nbOfStates, std::vector<StateSpaceDimension *> dimensions);
	void setPolicy(Policy *p);
	void setTransitionMatrix(TransitionMatrix *m);
	void setRewards(Rewards *r);
	State getState(Processor *proc, Queue *readyQueue, Queue *waitQueue); /*TODO Is this actually needed ?*/
	StateInternal getStateInternal(Processor *proc, Queue *readyQueue, Queue *waitQueue);
	State convertState(StateInternal);

	Policy *policy;
	TransitionMatrix *matrix;
	Rewards *rewards;
	int nbOfStates;
	std::vector<StateSpaceDimension *> dimensions;
	StateInternal currentState;
};




class StateSpaceBuilder
{
public:
	StateSpace *getStateSpace();
	void addDimension(StateSpaceDimension *dimension);
private:
	std::vector<StateSpaceDimension *> dimensions;


	int nbOfStates{1};
	int nbOfDimensions{0};
};


}




#endif
