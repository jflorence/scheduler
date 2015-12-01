#ifndef MDPREWARDS_H
#define MDPREWARDS_H

#include <vector>

class MdpRewards
{
public:
	MdpRewards(int nbOfStates, int nbOfActions);	
	double getReward(MdpState, MdpAction, double reward);
	void setReward(MdpState state, MdpAction action, double reward);

private:
	std::unordered_map<std::pair<int, int>, double> rewards; /*FIXME this is bad practice*/
	int nbOfStates;
	int nbOfActions;
};


#endif
