#ifndef MDP_H
#define MDP_H


#include <vector>
#include <map>



typedef int MdpState;
typedef enum MdpAction{minFreq, maxFreq, off} MdpAction;


class Mdp
{
public:
	Mdp(int nbStates, int nbActions);
	~Mdp();
	void setState(MdpState state);
	MdpState getState(void);
	MdpAction getAction(MdpState state);
	void generatePolicy(void);
private:
	MdpState currentState;
	const int nbStates;
	const int nbActions;
	vector< vector< vector<double> > > transitionMatrix;
	map<MdpState, MdpAction> policy;
};

#endif
