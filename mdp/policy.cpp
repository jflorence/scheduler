#include "policy.h"
#include "../randomGenerator.h"


using namespace Mdp;


Policy::Policy(int nbOfStates) :
	policy(std::vector<std::vector<double>>(nbOfStates, std::vector<double>(nbOfActions)))
{
	initializeRandomly();
}



/*TODO: this only works if all actions can be performed from all states,
which is not the case for generic MDPs.*/
void Policy::initializeRandomly()
{
	RandomGenerator *generator = RandomGenerator::getRandomGenerator();
	/*FIXME: this might mess the generator used to generate tasks,
	and therefore the comparison with other freqGovernors be invalid.*/
	
	ActionSpace *actionSpace = ActionSpace::getActionSpace();
	for (int i = 0; i < nbOfStates; i++)
	{
		std::vector<double> vector = generator->drawDistribution(actionSpace->size());
		update(i, vector);
	}
}


void Policy::update(State state, std::vector<double> vector)
{
	policy[state] = vector;
}

std::vector<double> Policy::getActionVector(State state)
{
	return policy[state];
}



