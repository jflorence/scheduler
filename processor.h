#ifndef PROCESSOR_H
#define PROCESSOR_H

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
private:
	const double maxFreq{2.0};
	const double minFreq{1.0};
	double usage{0.0};
	/*FIXME I have no clue about what is a good alpha value.
	It depends on the UsageUpdate event period and on the governor invocation period.*/
	double alpha{0.7};
	Process *runningTask{nullptr};

	TemperatureModel *temperatureModel{nullptr};

	double leakage{1.0};
	double capa{1.0};
	double power{0.0};
	double energy{0.0};
	double freq{1.0};



};


#endif
