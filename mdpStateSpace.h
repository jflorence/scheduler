#ifndef MDPSTATESPACE_H
#define MDPSTATESPACE_H

class Queue;
class Processor;
class MdpPolicy;
class MdpTransitionMatrix;
class MdpRewards;
typedef std::pair<int, int> MdpState;






class MdpStateSpace
{
	friend class MdpStateSpaceBuilder;
public:
	MdpStateSpace(int nbOfStates);

	void updateRewards(double currentReward);
	MdpAction selectAction(Processor *proc, Queue *readyQueue, Queue *waitQueue, double reward);
	void setPolicy(Policy *p);
	void setTransitionMatrix(TransitionMatrix *m);
	void setRewards(Rewards *r);

private:
	MdpState getState(Processor *proc, Queue *readyQueue, Queue *waitQueue);
	Policy *policy;
	TransitionMatrix *matrix;
	Rewards *rewards;
	int nbOfStates;
};




class MdpStateSpaceBuilder
{
public:
	MdpStateSpace *getStateSpace();
	void addReadyQueueSize();
	void addWaitQueueSize();
	void addFrequency();
	void addTemperature();
	void addMissRate();
private:
	bool withReadyQueue{false};
	bool withWaitQueue{false};
	bool withFrequency{false};
	bool withTemperature{false};
	bool withMissRate{false};


	int readyQueueIndex;
	int waitQueueIndex;
	int frequencyIndex;
	int temperatureIndex;
	int missRateIndex;



	int nbOfStates{1};
	int nbOfDimensions{0};
};







#endif
