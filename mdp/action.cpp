#include "action.h"
#include <cassert>


MdpActionSpace *MdpActionSpace::space = nullptr;

MdpActionSpace *MdpActionSpace::getActionSpace()
{
        if (space == nullptr)
        {
                space = new MdpActionSpace();
        }
        return space;
}

MdpActionSpace::MdpActionSpace()
{
	actions = std::vector<std::string>(MdpAction::nbOfActions);
	actions[decreaseFreq] = "decreaseFreq";
	actions[increaseFreq] = "increaseFreq";

}

int MdpActionSpace::size()
{
	assert(MdpAction::nbOfActions == actions.size());
	return actions.size();
}




std::string MdpActionSpace::getActionName(MdpAction action)
{
	return actions[action];
}
