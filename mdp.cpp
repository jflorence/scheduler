#include "mdp.h"



Mdp::Mdp(int nbS, int nbA) : nbStates(nbS), nbActions(nbA)
{
	/*FIXME there must be a better way to do this*/
	transitionMatrix.resize(nbActions);
	for (int i = 0; i < nbStates, i++)
	{
		transitionMatrix[i].resize(nbActions);
		for (int i = 0; i < nbStates; i++)
		{
			transitionMatrix[i][j].resize(nbActions);
		}
	}
	
}

Mdp::~Mdp()
{
}




void Mdp::setState(MdpState state)
{
	currentState = state;
}

MdpState Mdp::getState(void)
{
	return currentState;

}




MdpAction Mdp::getAction(MdpState state)
{
	return policy.at(state);
}


void Mdp::generatePolicy(void)
{
	return ;
}








