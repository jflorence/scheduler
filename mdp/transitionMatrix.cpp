#include "transitionMatrix.h"
#include "../randomGenerator.h"



using namespace Mdp;


TransitionMatrix::TransitionMatrix(int S, int A) :
	matrix(new double[S*S*A]), nbOfStates(S), nbOfActions(A)
{
	initializeRandomly();
}

TransitionMatrix::~TransitionMatrix()
{
	delete[] matrix;
}



double TransitionMatrix::get(State from, State to, Action action)
{
	return matrix[from*nbOfStates*nbOfActions + action*nbOfStates + to];
}

void TransitionMatrix::set(State from, State to, Action action, double proba)
{
	matrix[from*nbOfStates*nbOfActions + action*nbOfStates + to] = proba;
}


void TransitionMatrix::initializeRandomly()
{
	RandomGenerator *generator = RandomGenerator::getRandomGenerator();
	for (int i = 0; i < nbOfStates; i++)
	{
		for (int j = 0; j < nbOfActions; j++)
		{
			std::vector<double> vector = generator->drawDistribution(nbOfStates);
			for (int k = 0; k < nbOfStates; k++)
			{
				set(i, k, (Action) j, vector[k]);
			}
		}
	}
}
