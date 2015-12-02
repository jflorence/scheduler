#ifndef MDPPOLICY_H
#define MDPPOLICY_H

#include <vector>
#include "action.h"
#include "state.h"

class MdpPolicy
{
public:
	MdpPolicy(int nbOfStates);
	void update(MdpState state, std::vector<double> vector);
	MdpAction getAction(MdpState state);
	std::vector<double> getActionVector(MdpState state);
	void initializeRandomly();
private:
	std::vector<std::vector<double>> policy;
	int nbOfStates;
	int nbOfActions;
};

#endif
