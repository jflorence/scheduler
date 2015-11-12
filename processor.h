#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "temperatureModel.h"

class Process;
class TemperatureModel;
class Processor
{
public:
	static Processor *getInstance();
private:
	static Processor *proc;
public:
	double getFreq();
	void setFreq(double);
	double getMinFreq();
	double getMaxFreq();
	double getUsage();
	void updateUsage(bool isBusy);
	bool isRunning(Process *p);
	void setRunning(Process *p);
	Process *getRunningTask();
	void setTemperatureModel(TemperatureModel *);
	void updateTemperature(double timeInterval);
	void printTemperatureReport();
	bool isBusy();
	void setBusy(bool busy);
private:
	const double maxFreq{2.0};
	const double minFreq{1.0};
	double usage{0.0};
	/*FIXME I have no clue about what is a good alpha value.
	It depends on the UsageUpdate event period and on the governor invocation period.*/
	double alpha{0.7};
	double freq{1.0};
	Process *runningTask{nullptr};

	struct PowerParams powerParams;
	TemperatureModel *temperatureModel{nullptr};

	bool busy{false};

};


#endif
