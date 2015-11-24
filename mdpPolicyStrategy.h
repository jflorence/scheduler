#ifndef MDPPOLICYSTRATEGY_H
#define MDPPOLICYSTRATEGY_H


class Policy;
class TransitinoMatrix;
class Rewards;


class MdpPolicyStrategy
{
public:
	virtual void updatePolicy(Policy *policy, TransitionMatrix *mat, Rewards *rewards)=0;
};



#endif
