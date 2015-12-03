#include "action.h"
#include <cassert>

using namespace Mdp;

ActionSpace *ActionSpace::space = nullptr;

ActionSpace *ActionSpace::getActionSpace()
{
        if (space == nullptr)
        {
                space = new ActionSpace();
        }
        return space;
}

ActionSpace::ActionSpace()
{
	actions = std::vector<std::string>(Action::nbOfActions);
	actions[minFreq] = "minFreq";
	actions[maxFreq] = "maxFreq";

}

int ActionSpace::size()
{
	assert(Action::nbOfActions == actions.size());
	return actions.size();
}




std::string ActionSpace::getActionName(Action action)
{
	return actions[action];
}
