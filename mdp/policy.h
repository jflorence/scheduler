#ifndef POLICY_H
#define POLICY_H

#include <vector>
#include "state.h"
#include "action.h"


namespace Mdp
{

class Policy
{
public:
	Policy(int nbOfStates, int nbOfActions);
	void update(State state, std::vector<double> vector);
	Action getAction(State state);
	std::vector<double> getActionVector(State state);
	void initializeRandomly();
	void initializeFromFile();
protected:
	std::vector<std::vector<double>> policy;
	int nbOfStates;
	int nbOfActions;
};




}




#endif



















