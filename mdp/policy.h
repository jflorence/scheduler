#ifndef MDPPOLICY_H
#define MDPPOLICY_H


#include <vector>
#include "action.h"
#include "state.h"

namespace Mdp
{

class Policy
{
public:
	Policy(int nbOfStates);
	void update(State state, std::vector<double> vector);
	Action getAction(State state);
	std::vector<double> getActionVector(State state);
	void initializeRandomly();
private:
	std::vector<std::vector<double>> policy;
	int nbOfStates;
	int nbOfActions;
};



}
#endif
