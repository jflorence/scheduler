#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <ctime>

class SchedulingSimulator
{
public:
	void createRealTimeTask(double startTime, double period, double deadline, double aow);
	void createInteractiveProcess(double startTime);
	void endSimulation(double time);
	void seedRandomGenerator(time_t seed);
	void setUsageCalculationTimeout(double start, double interval);
	void setFreqUpdate(double start, double interval);
	void setSchedulerTimeout(double start, double interval);
	void startScheduler();
private:
	double previousTime{0.0};
};
#endif
