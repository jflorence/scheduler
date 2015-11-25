#include "mdpAction.h"


MdpAction::MdpAction(std::string str)
{
	name = str;
	id = idCounter++;
}



MdpActionSpace *MdpActionSpace::space = nullptr;

MdpActionSpace *MdpActionSpace::getActionSpace()
{
        if (space == nullptr)
        {
                space = new MdpActionSpace();
                space->actions->push_back(MdpAction("increaseFreq"));
                space->actions->push_back(MdpAction("decreaseFreq"));
        }
        return space;
}



int MdpActionSpace::size()
{
	return actions.size();
}




