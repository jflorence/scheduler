#include "mdpStateSpace.h"
#include "mdpPolicy.h"
#include "mdpTransitionMatrix.h"
#include "mdpRewards.h"

MdpStateSpace::MdpStateSpace(int N) : nbOfStates(N) {}



MdpState MdpStateSpace::getState(Processor *proc, Queue *readyQueue, Queue *waitQueue)
{
/*FIXME TODO*/
	MdpState state;
	return state;
}

void MdpStateSpace::updateRewards(double currentReward)
{
/*FIXME TODO*/
	return;
}


MdpAction MdpStateSpace::selectAction(Processor *proc, Queue *readyQueue, Queue *waitQueue, double reward)
{
	MdpAction action;
	return action;
}



void MdpStateSpace::setPolicy(Policy *p)
{
	policy = p;
}

void MdpStateSpace::setTransitionMatrix(TransitionMatrix *m)
{
	matrix = m;
}

void MdpStateSpace::setRewards(Rewards *r)
{
	rewards = r;
}















MdpStateSpace *MdpStateSpaceBuilder::getStateSpace()
{
	MdpStateSpace *statespace = new MdpStateSpace();
	int nbOfActions = MdpActionState::getActionState()->size();
	MdpPolicy *policy = new MdpPolicy(nbOfStates);
	MdpTransitionMatrix matrix = new MdpTransitionMatrix(nbOfStates, nbOfActions);
	MdpRewards rewards = new MdpRewards(nbOfStates, nbOfActions);
	return stateSpace;
}


void MdpStateSpaceBuilder::addReadyQueue()
{
	nbOfStates *= Queue::getReadyQueue()->getMaxSize();
	readyQueueIndex = nbOfDimensions;
	nbOfDimensions++;
	withReadyQueue = true;
}

void MdpStateSpaceBuilder::addWaitQueue()
{
	nbOfStates *= Queue::getWaitQueue()->getMaxSize();
	waitQueueIndex = nbOfDimensions;
	nbofDimensions++;
	withWaitQueue++;
}

void MdpStateSpaceBuilder::withFrequency()
{
	nbOfStates *= 2; /*TODO how many states for the freq ??*/
	frequencyIndex = nbOfDimensions;
	nbOfDimensions++;
	withWaitQueue = true;
}

void MdpStateSpaceBuilder::withTemperature()
{
	nbOfStates *= 2; /*TODO how many states for the temp??*/
	temperatureIndex = nbOfDimensions;
	nbOfDimensions++;
	withTemperature = true;
}

void MdpStateSpaceBuilder::withMissRate()
{
	nbOfStates *= 2; /*TODO: how many states for the miss rate?*/
	missRateIndex = nbOfDimensions;
	nbOfDimensions++;
	withMissRate = true;
}






























