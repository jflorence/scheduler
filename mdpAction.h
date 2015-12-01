#ifndef MDPACTION_H
#define MDPACTION_H

#include <vector>
#include <string>


class MdpAction
{
public:
	static int idCounter;
public:
	MdpAction();
	MdpAction(std::string);
	std::string getName();
	int getId();
private:
	std::string name;
	int id;
};

class MdpActionSpace
{
public:
	static MdpActionSpace *getActionSpace();
private:
	static MdpActionSpace *space;
public:
	int size();
private:
	std::vector<MdpAction> actions;
};


#endif
