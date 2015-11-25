#ifndef MDPACTION_H
#define MDPACTION_H

#include <vector>
#include <string>


class MdpAction
{
public:
	static int idCounter{0};
public:
	MdpAction(std::string);
	std::string getName();
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
	vector<MdpAction> actions;
};


#endif
