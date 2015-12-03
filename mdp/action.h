#ifndef MDPACTION_H
#define MDPACTION_H

#include <string>
#include <tuple>
#include <vector>
namespace Mdp
{

class ActionSpace
{
public:
	enum Action
	{
		minFreq, maxFreq, nbOfActions
	};
	static ActionSpace *getActionSpace();
private:
	static ActionSpace *space;
public:
	ActionSpace();
	int size();
	std::string getActionName(Action);
private:
	std::vector<std::string> actions;
};

typedef enum ActionSpace::Action Action;

}
#endif
