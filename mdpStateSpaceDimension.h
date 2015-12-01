#ifndef MDPSTATESPACEDIMENSION_H
#define MDPSTATESPACEDIMENSION_H

#include <string>

class MdpStateSpaceDimension
{
public:
	virtual ~MdpStateSpaceDimension(){};
	virtual std::string getName()=0;
	virtual int getPosition()=0; /*Gets the current state of the system in that particular dimension*/
	virtual int getNumberOfPositions()=0;
	void setIndex(int i);
	int getIndex();
private:
	int index;
};





class MdpReadyQueueDimension : public MdpStateSpaceDimension
{
public:
	~MdpReadyQueueDimension(){};
	std::string getName();
	int getPosition();
	int getNumberOfPositions();
};

class MdpWaitQueueDimension : public MdpStateSpaceDimension
{
public:
	~MdpWaitQueueDimension(){}
	std::string getName();
	int getPosition();
	int getNumberOfPositions();
};

class MdpFrequencyDimension : public MdpStateSpaceDimension
{
public:
	~MdpFrequencyDimension(){};
	std::string getName();
	int getPosition();
	int getNumberOfPositions();
};

class MdpTemperatureDimension : public MdpStateSpaceDimension
{
public:
	~MdpTemperatureDimension(){};
	std::string getName();
	int getPosition();
	int getNumberOfPositions();
};

class MdpMissRateDimension : public MdpStateSpaceDimension
{
public:
	~MdpMissRateDimension(){};
	std::string getName();
	int getPosition();
	int getNumberOfPositions();
};



#endif
