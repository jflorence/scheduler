#ifndef STATESPACEBUILDER_H
#define STATESPACEBUILDER_H

#include <vector>

namespace Mdp
{
class StateSpace;
class StateSpaceDimension;


class StateSpaceBuilder
{
public:
	StateSpace *getStateSpace();
	void addDimension(StateSpaceDimension *dimension);
private:
	std::vector<StateSpaceDimension *> dimensions;


	int nbOfStates{1};
	int nbOfDimensions{0};
};








}


#endif
