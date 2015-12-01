#ifndef MDPPOLICY_H
#define MDPPOLICY_H

#include <unordered_map>
#include <tuple>
#include "mdpAction.h"
#include "mdpStateSpace.h"

class MdpPolicy
{
public:
	MdpPolicy(int nbOfStates);
	void set(std::unordered_map<MdpState, MdpAction> p);
	void update(MdpState state, MdpAction action);
	MdpAction getAction(MdpState state);
private:
	std::unordered_map<MdpState, MdpAction> policy;
	int nbOfStates;
	int nbOfActions;
};

#endif
