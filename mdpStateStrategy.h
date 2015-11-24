#ifndef MDPSTATESTRATEGY_H
#define MDPSTATESTRATEGY_H

class Queue;
class Processor;

typedef int MdpState;

class mdpStateStrategy
{
public:
	virtual MdpState getState(Processor *proc, Queue *readyQueue, Queue *waitQueue)=0;
	virtual int getNumberOfStates()=0;
	virtual void updateRewards(double currentReward)=0;
	virtual MdpAction selectAction(Processor *proc, Queue *readyQueue, Queue *waitQueue, double reward);
	
};











#endif
