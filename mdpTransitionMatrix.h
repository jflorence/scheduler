#ifndef MDPTRANSITIONMATRIX_H
#define MDPTRANSITIONMATRIX_H

#include <vector>

class MdpTransitionMatrix
{
public:
	MdpTransitionMatrix(int nbOfStates, int nbOfActions);
	~MdpTransitionMatrix;
	void set(MdpState from, MdpState to, MdpAction action, double proba);
	double get(MdpState from, MdpState to, MdpAction action);
private:
	double *matrix{nullptr};
};

#endif
