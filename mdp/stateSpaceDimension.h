#ifndef MDPSTATESPACEDIMENSION_H
#define MDPSTATESPACEDIMENSION_H

#include <string>



namespace Mdp
{



class StateSpaceDimension
{
public:
	virtual ~StateSpaceDimension(){};
	virtual std::string getName()=0;
	virtual int getPosition()=0; /*Gets the current state of the system in that particular dimension*/
	virtual int getNumberOfPositions()=0;
	void setIndex(int i);
	int getIndex();
private:
	int index;
};





class ReadyQueueDimension : public StateSpaceDimension
{
public:
	~ReadyQueueDimension(){};
	std::string getName();
	int getPosition();
	int getNumberOfPositions();
};

class WaitQueueDimension : public StateSpaceDimension
{
public:
	~WaitQueueDimension(){}
	std::string getName();
	int getPosition();
	int getNumberOfPositions();
};

class FrequencyDimension : public StateSpaceDimension
{
public:
	~FrequencyDimension(){};
	std::string getName();
	int getPosition();
	int getNumberOfPositions();
};

class TemperatureDimension : public StateSpaceDimension
{
public:
	~TemperatureDimension(){};
	std::string getName();
	int getPosition();
	int getNumberOfPositions();
};

class MissRateDimension : public StateSpaceDimension
{
public:
	~MissRateDimension(){};
	std::string getName();
	int getPosition();
	int getNumberOfPositions();
};


}
#endif
