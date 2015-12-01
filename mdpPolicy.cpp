#include "mdpPolicy.h"


MdpPolicy::MdpPolicy(int nbOfStates) : policy(unordered_map(nbOfStates))
{	
}

void MdpPolicy::set(std::unordered_map<MdpState, MdpAction> p)
{
	policy = p;
}

void MdpPolicy::update(MdpState state, MdpAction action)
{
	policy[state] = action;
}

MdpAction MdpPolicy::getAction(MdpState state)
{
	return policy(state);
}



