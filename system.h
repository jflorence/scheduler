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
	void updateTemperature();
	Processor *getProc();
private:
	Processor proc;
};






#endif






