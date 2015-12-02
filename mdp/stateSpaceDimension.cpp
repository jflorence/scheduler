#include "stateSpaceDimension.h"
#include "../queue.h"
#include "../processor.h"
#include "../system.h"
using namespace Mdp;


void StateSpaceDimension::setIndex(int i)
{
	index = i;
}

int StateSpaceDimension::getIndex()
{
	return index;
}







std::string ReadyQueueDimension::getName()
{
	return "Ready queue dimension";
}

int ReadyQueueDimension::getPosition()
{
	return Queue::getReadyQueue()->size();
}

int ReadyQueueDimension::getNumberOfPositions()
{
	return Queue::getReadyQueue()->getMaxSize()+1;
}







std::string WaitQueueDimension::getName()
{
	return  "Wait queue dimension";	
}

int WaitQueueDimension::getPosition()
{
	return Queue::getWaitQueue()->size();
}

int WaitQueueDimension::getNumberOfPositions()
{
	return Queue::getWaitQueue()->getMaxSize()+1;
}









std::string FrequencyDimension::getName()
{
	return "Frequency dimension";
}

int FrequencyDimension::getPosition()
{
	int pos;
	if (System::getInstance()->getProc()->getMinFreq() == System::getInstance()->getProc()->getFreq())
	{
		pos = 0;
	}
	else
	{
		pos = 1;
	}
	return pos;
}

int FrequencyDimension::getNumberOfPositions()
{
	return 2;
}








std::string TemperatureDimension::getName()
{
	return "Temperature dimension";
}

int TemperatureDimension::getPosition()
{
	return -1;
}

int TemperatureDimension::getNumberOfPositions()
{
	return 2;
}





std::string MissRateDimension::getName()
{
	return "Miss rate dimension";
}

int MissRateDimension::getPosition()
{
	return -1;
}

int MissRateDimension::getNumberOfPositions()
{
	return -1;
}








