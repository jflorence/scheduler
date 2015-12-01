#include "mdpAction.h"

int MdpAction::idCounter = 0;

MdpAction::MdpAction(std::string str)
{
	name = str;
	id = idCounter++;
}

MdpAction::MdpAction()
{
	name = "noName";
	id = idCounter++;
}

int MdpAction::getId()
{
	return id;
}



MdpActionSpace *MdpActionSpace::space = nullptr;

MdpActionSpace *MdpActionSpace::getActionSpace()
{
        if (space == nullptr)
        {
                space = new MdpActionSpace();
                space->actions.push_back(MdpAction("increaseFreq"));
                space->actions.push_back(MdpAction("decreaseFreq"));
        }
        return space;
}



int MdpActionSpace::size()
{
	return actions.size();
}




