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
		decreaseFreq, increaseFreq, nbOfActions
	};
	static ActionSpace *getActionSpace();
private:
	static ActionSpace *space;
public:
	int size();
	std::string getActionName(Action);
private:
	ActionSpace();
	std::vector<std::string> actions;
};

typedef enum ActionSpace::Action Action;

}
#endif
