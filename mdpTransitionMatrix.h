#ifndef MDPTRANSITIONMATRIX_H
#define MDPTRANSITIONMATRIX_H

#include <vector>
#include "mdpState.h"
#include "mdpAction.h"



class MdpTransitionMatrix
{
public:
	MdpTransitionMatrix(int nbOfStates, int nbOfActions);
	~MdpTransitionMatrix();
	void set(MdpState from, MdpState to, MdpAction action, double proba);
	double get(MdpState from, MdpState to, MdpAction action);
	void initializeRandomly();
private:
	double *matrix{nullptr};
	int nbOfStates;
	int nbOfActions;
};

#endif
