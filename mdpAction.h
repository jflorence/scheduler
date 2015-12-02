#ifndef MDPACTION_H
#define MDPACTION_H

#include <string>
#include <tuple>
#include <vector>


class MdpActionSpace
{
public:
	enum MdpAction
	{
		decreaseFreq, increaseFreq, nbOfActions
	};
	static MdpActionSpace *getActionSpace();
private:
	static MdpActionSpace *space;
public:
	int size();
	std::string getActionName(MdpAction);
private:
	MdpActionSpace();
	std::vector<std::string> actions;
};

typedef enum MdpActionSpace::MdpAction MdpAction;


#endif
