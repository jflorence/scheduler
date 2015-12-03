#include "policy.h"

#include <cassert>
#include "../randomGenerator.h"

using namespace Mdp;

Policy::Policy(int S, int A) :
	policy(std::vector<std::vector<double>>(S, std::vector<double>(A))),
	nbOfStates(S), nbOfActions(A)
{}



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

void Policy::initializeFromFile()
{
	/*FIXME TODO*/
}


void Policy::update(State state, std::vector<double> vector)
{
        policy[state] = vector;
}


std::vector<double> Policy::getActionVector(State state)
{
	return policy[state];
}

Action Policy::getAction(State state)
{
	std::vector<double> vector = getActionVector(state);
	double d = RandomGenerator::getRandomGenerator()->drawUniform(0.0, 1.0);
	double cumulative = 0.0;
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		cumulative += vector[i];
		if (d <= cumulative)
		{
			return (Action) i;
		}
	}
	assert (0 == 1);
	return (Action) 0;
}










