#include "rewards.h"

MdpRewards::MdpRewards(int S, int A) :
	nbOfStates(S),
	nbOfActions(A),
	rewards(std::vector<std::vector<double>>(S, std::vector<double>(A, 0.0)))
{
}

double MdpRewards::getReward(MdpState state, MdpAction action)
{
	return rewards[state][action];
}

void MdpRewards::setReward(MdpState state, MdpAction action, double reward)
{
	rewards[state][action] = reward;
}







