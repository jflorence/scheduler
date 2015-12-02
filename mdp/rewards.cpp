#include "rewards.h"

using namespace Mdp;

Rewards::Rewards(int S, int A) :
	nbOfStates(S),
	nbOfActions(A),
	rewards(std::vector<std::vector<double>>(S, std::vector<double>(A, 0.0)))
{
}

double Rewards::getReward(State state, Action action)
{
	return rewards[state][action];
}

void Rewards::setReward(State state, Action action, double reward)
{
	rewards[state][action] = reward;
}







