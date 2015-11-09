#include <iostream>
#include <ctime>
#include "schedulingSimulator.h"



int main()
{
	std::cout << "Hello!\n";
	
	SchedulingSimulator simulator;

	simulator.seedRandomGenerator(time(NULL));
	
	/*
	simulator.createRealTimeTask(0.0, 35.0, 25.0, 10.0);
	simulator.createRealTimeTask(0.0, 25.0, 6.0, 6.0);
	simulator.createRealTimeTask(0.0, 15.0, 15.0, 7.0);
	*/
	simulator.createInteractiveProcess(1.0);
	simulator.createInteractiveProcess(1.0);

	simulator.setUsageCalculationTimeout(1.0, 2.0);
	simulator.setFreqUpdate(1.0, 10.0);
	simulator.setSchedulerTimeout(1.0, 2.0);
	
	simulator.endSimulation(100.0);	

	simulator.startScheduler();

	return 0;
}

































