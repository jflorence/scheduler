#ifndef PROCESS_H
#define PROCESS_H

#include <iterator>
#include <cmath>

class Event;

class Process
{
public:
	static Process *createJob(int pid, double aow/*amount of work*/);
	static Process *createProcess(double cpuLambda, double ioLambda);
	static Process *createRealTimeTask(double aow, double T, double dl, int pid);
	static int getNewPid();
private:
	int pid;
	double *cpuBurst;/*This is an array of aow*/
	double *ioBurst;/*This is an array of times spent waiting*/
	int currentBurst;
	int nbBursts; /*This is the nb of cpu bursts. there qre n-1 io bursts.*/
	int priority;
	bool RT{false};
	double deadline{INFINITY};
	double period{INFINITY};
public:
	Process(int p, int nbBursts, double *cpuBursts, double *ioBursts, int priority = 0);
	Process(const Process& task);
	~Process();
	int getPid(void);
	void updateCurrentAow(double aow);
	bool advanceBurst();
	void decrementBurst();
	double getCurrentCpuAow();
	double getCurrentIoTime();
	const double powerCoeff{1.0};
	void setRtParams(double dl, double T);
	bool isRealTime();
	double getPeriod();
};







#endif
