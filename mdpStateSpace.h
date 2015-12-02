#ifndef MDPSTATESPACE_H
#define MDPSTATESPACE_H

#include <vector>
#include "mdpStateSpaceDimension.h"
#include "mdpAction.h"
#include "mdpState.h"
class Queue;
class Processor;
class MdpPolicy;
class MdpTransitionMatrix;
class MdpRewards;
typedef std::vector<int> MdpStateInternal;






class MdpStateSpace
{
	friend class MdpStateSpaceBuilder;
public:

	void updateRewards(double currentReward);
	MdpAction selectAction(Processor *proc, Queue *readyQueue, Queue *waitQueue, double reward);
	~MdpStateSpace();

private:
	/*state space has to be constructed with the builder*/
	MdpStateSpace(int nbOfStates, std::vector<MdpStateSpaceDimension *> dimensions);
	void setPolicy(MdpPolicy *p);
	void setTransitionMatrix(MdpTransitionMatrix *m);
	void setRewards(MdpRewards *r);
	MdpState getState(Processor *proc, Queue *readyQueue, Queue *waitQueue); /*TODO Is this actually needed ?*/
	MdpStateInternal getStateInternal(Processor *proc, Queue *readyQueue, Queue *waitQueue);
	MdpState convertState(MdpStateInternal);

	MdpPolicy *policy;
	MdpTransitionMatrix *matrix;
	MdpRewards *rewards;
	int nbOfStates;
	std::vector<MdpStateSpaceDimension *> dimensions;
	MdpStateInternal currentState;
};




class MdpStateSpaceBuilder
{
public:
	MdpStateSpace *getStateSpace();
	void addDimension(MdpStateSpaceDimension *dimension);
private:
	std::vector<MdpStateSpaceDimension *> dimensions;


	int nbOfStates{1};
	int nbOfDimensions{0};
};







#endif
