#include "mdpRewards.h"

MdpRewards::MdpRewards(int S, int A) : nbOfStates(S), nbOfActions(A), rewards(std::vector::vector(S, <std::vector<double>>(A)))
{
}

double MdpRewards::getReward(MdpState state, MdpAction action)
{
	return rewards[std::pair<int, int>(state, action.getId())];
}

void MdpRewards::setReward(MdpState state, MdpAction action, double reward)
{
	rewards[state]
}







