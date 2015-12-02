#ifndef MDPLEARNINGSTRATEGY_H
#define MDPLEARNINGSTRATEGY_H


class Mdp::Policy;
class Mdp::TransitionMatrix;
class Mdp::Rewards;

namespace Mdp
{

class LearningStrategy
{
public:
	virtual void update(Policy *policy, TransitionMatrix *mat, Rewards *rewards)=0;
};


}
#endif
