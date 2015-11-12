#include "system.h"
#include "processor.h"
System *System::instance = nullptr;

System *System::getInstanec()
{
	if (instance == nullptr)
		instance = new System();
	return instance;
}

void System::updateTemperature(double timeInterval)
{

	proc.updateTemperature(timeInterval);

}

Processor *System::getProc()
{
	return &proc;
}


