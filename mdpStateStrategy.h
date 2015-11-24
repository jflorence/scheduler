#ifndef MDPSTATESTRATEGY_H
#define MDPSTATESTRATEGY_H

class Queue;
class Processor;

typedef int MdpState;

class mdpStateStrategy
{
public:
	virtual MdpState getState(Processor *proc, Queue *readyQueue, Queue *waitQueue)=0;

};











#endif
