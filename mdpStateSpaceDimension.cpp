#include "mdpStateSpaceDimension.h"
#include "queue.h"

void MdpStateSpaceDimension::setIndex(int i)
{
	index = i;
}

int MdpStateSpaceDimension::getIndex()
{
	return index;
}







std::string MdpReadyQueueDimension::getName()
{
	return "Ready queue dimension";
}

int MdpReadyQueueDimension::getPosition()
{
	return Queue::getReadyQueue()->getMaxSize();
}

int MdpReadyQueueDimension::getNumberOfPositions()
{
	return -1;
}







std::string MdpWaitQueueDimension::getName()
{
	return  "Wait queue dimension";	
}

int MdpWaitQueueDimension::getPosition()
{
	return -1;
}

int MdpWaitQueueDimension::getNumberOfPositions()
{
	return Queue::getWaitQueue()->getMaxSize();
}









std::string MdpFrequencyDimension::getName()
{
	return "Frequency dimension";
}

int MdpFrequencyDimension::getPosition()
{
	return -1;
}

int MdpFrequencyDimension::getNumberOfPositions()
{
	return 2;
}








std::string MdpTemperatureDimension::getName()
{
	return "Temperature dimension";
}

int MdpTemperatureDimension::getPosition()
{
	return -1;
}

int MdpTemperatureDimension::getNumberOfPositions()
{
	return 2;
}





std::string MdpMissRateDimension::getName()
{
	return "Miss rate dimension";
}

int MdpMissRateDimension::getPosition()
{
	return -1;
}

int MdpMissRateDimension::getNumberOfPositions()
{
	return -1;
}









