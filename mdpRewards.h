#ifndef MDPREWARDS_H
#define MDPREWARDS_H

#include <vector>

#include "mdpAction.h"
#include "mdpState.h"
class MdpRewards
{
public:
	MdpRewards(int nbOfStates, int nbOfActions);	
	double getReward(MdpState, MdpAction);
	void setReward(MdpState state, MdpAction action, double reward);

private:
	int nbOfStates;
	int nbOfActions;
	std::vector<std::vector<double>> rewards;
};


#endif
