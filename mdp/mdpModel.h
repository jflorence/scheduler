#ifndef MDPMODEL_H
#define MDPMODEL_H

#include "action.h"

namespace Mdp
{

class StateSpace;
class TransitionMatrix;
class Rewards;
class Policy;
class LearningStrategy;

class MdpModel
{
public:
	MdpModel(StateSpace *stateSpace);
	~MdpModel();
	Action selectAction();
private:
	StateSpace *stateSpace;
	TransitionMatrix *matrix;
	Rewards *rewards;
	Policy *policy;
	LearningStrategy *learningStrategy;
	ActionSpace actionSpace;
};


}
#endif
