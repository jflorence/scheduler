#ifndef MDPLEARNINGSTRATEGY_H
#define MDPLEARNINGSTRATEGY_H



namespace Mdp
{
class Policy;
class TransitionMatrix;
class Rewards;

class LearningStrategy
{
public:
	LearningStrategy(Policy *policy, Rewards *rewards, TransitionMatrix *matrix);
	virtual ~LearningStrategy();
	virtual void updateModel()=0;
	virtual void initializeModel()=0;
protected:
	Policy *policy;
	Rewards *rewards;
	TransitionMatrix *matrix;
};


}
#endif
