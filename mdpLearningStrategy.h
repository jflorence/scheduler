#ifndef MDPLEARNINGSTRATEGY_H
#define MDPLEARNINGSTRATEGY_H


class Policy;
class TransitionMatrix;
class Rewards;


class MdpLearningStrategy
{
public:
	virtual void update(Policy *policy, TransitionMatrix *mat, Rewards *rewards)=0;
};



#endif
