#include "mdpPolicy.h"


MdpPolicy::MdpPolicy(int nbOfStates)
{}

MdpAction mdpPolicy::getAction(MdpState state)
{
	return policy[state];
}



