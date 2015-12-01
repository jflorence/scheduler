#include "mdpTransitionMatrix.h"


MdpTransitionMatrix::MdpTransitionMatrix(int S, int A) : matrix(new double[S*S*A]), nbOfStates(S), nbOfActions(A)
{
}

MdpTransitionMatrix::~MdpTransitionMatrix()
{
	delete[] matrix;
}



double get(MdpState from, MdpState to, MdpAction action)
{
	return matrix[from*nbOfStates*nbOfActions + action*nbOfStates + to];
}

void set(MdpState from, MdpState to, MdpAction action, double proba)
{
	matrix[from*nbOfStates*nbOfActions + action*nbOfStates + to] = proba;
}



