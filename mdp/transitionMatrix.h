#ifndef MDPTRANSITIONMATRIX_H
#define MDPTRANSITIONMATRIX_H

#include <vector>
#include "state.h"
#include "action.h"

namespace Mdp
{

class TransitionMatrix
{
public:
	TransitionMatrix(int nbOfStates, int nbOfActions);
	~TransitionMatrix();
	void set(State from, State to, Action action, double proba);
	double get(State from, State to, Action action);
	void initializeRandomly();
private:
	double *matrix{nullptr};
	int nbOfStates;
	int nbOfActions;
};


}

#endif
