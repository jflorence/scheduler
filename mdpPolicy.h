#ifndef MDPPOLICY_H
#define MDPPOLICY_H

#include <map>
#include <tuple>

class MdpPolicy
{
public:
	MdpPolicy(int nbOfStates);
	MdpAction getAction(MdpState state);
private:
	map<MdpState, MdpAction> policy;
};

#endif
