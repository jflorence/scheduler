#include "policy.h"
#include "../randomGenerator.h"

MdpPolicy::MdpPolicy(int nbOfStates) :
	policy(std::vector<std::vector<double>>(nbOfStates, std::vector<double>(nbOfActions)))
{
	initializeRandomly();
}



/*TODO: this only works if all actions can be performed from all states,
which is not the case for generic MDPs.*/
void MdpPolicy::initializeRandomly()
{
	RandomGenerator *generator = RandomGenerator::getRandomGenerator();
	/*FIXME: this might mess the generator used to generate tasks,
	and therefore the comparison with other freqGovernors be invalid.*/
	
	MdpActionSpace *actionSpace = MdpActionSpace::getActionSpace();
	for (int i = 0; i < nbOfStates; i++)
	{
		std::vector<double> vector = generator->drawDistribution(actionSpace->size());
		update(i, vector);
	}
}


void MdpPolicy::update(MdpState state, std::vector<double> vector)
{
	policy[state] = vector;
}

std::vector<double> MdpPolicy::getActionVector(MdpState state)
{
	return policy[state];
}



