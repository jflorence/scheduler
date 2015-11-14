#include "system.h"
#include "processor.h"
#include "simpleTemperatureModel.h"
System *System::instance = nullptr;

System *System::getInstance()
{
	if (instance == nullptr)
	{
		instance = new System();
		instance->proc = new Processor;
		instance->proc->setTemperatureModel(new SimpleTemperatureModel);
	}
	return instance;
}

void System::updateTemperature(double timeInterval)
{

	proc->updateTemperature(timeInterval);

}

Processor *System::getProc()
{
	return proc;
}



void System::printTemperatureReport()
{
	proc->printTemperatureReport();
}











