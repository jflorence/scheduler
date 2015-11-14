#ifndef SYSTEM_H
#define SYSTEM_H

#include "processor.h"

class System
{
public:
	static System *getInstance();
private:
	static System *instance;
public:
	void updateTemperature(double timeInterval);
	Processor *getProc();
	void printTemperatureReport();
private:
	Processor *proc;
};






#endif






