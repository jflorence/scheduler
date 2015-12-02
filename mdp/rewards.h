#ifndef MDPREWARDS_H
#define MDPREWARDS_H

#include <vector>

#include "action.h"
#include "state.h"

namespace Mdp
{


class Rewards
{
public:
	Rewards(int nbOfStates, int nbOfActions);	
	double getReward(State, Action);
	void setReward(State state, Action action, double reward);

private:
	int nbOfStates;
	int nbOfActions;
	std::vector<std::vector<double>> rewards;
};

}
#endif
