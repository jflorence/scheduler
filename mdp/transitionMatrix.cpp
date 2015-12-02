#include "transitionMatrix.h"
#include "../randomGenerator.h"

MdpTransitionMatrix::MdpTransitionMatrix(int S, int A) :
	matrix(new double[S*S*A]), nbOfStates(S), nbOfActions(A)
{
	initializeRandomly();
}

MdpTransitionMatrix::~MdpTransitionMatrix()
{
	delete[] matrix;
}



double MdpTransitionMatrix::get(MdpState from, MdpState to, MdpAction action)
{
	return matrix[from*nbOfStates*nbOfActions + action*nbOfStates + to];
}

void MdpTransitionMatrix::set(MdpState from, MdpState to, MdpAction action, double proba)
{
	matrix[from*nbOfStates*nbOfActions + action*nbOfStates + to] = proba;
}


void MdpTransitionMatrix::initializeRandomly()
{
	RandomGenerator *generator = RandomGenerator::getRandomGenerator();
	for (int i = 0; i < nbOfStates; i++)
	{
		for (int j = 0; j < nbOfActions; j++)
		{
			std::vector<double> vector = generator->drawDistribution(nbOfStates);
			for (int k = 0; k < nbOfStates; k++)
			{
				set(i, k, (MdpAction) j, vector[k]);
			}
		}
	}
}
