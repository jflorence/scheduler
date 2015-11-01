#ifndef PROCESS_H
#define PROCESS_H

#include <iterator>

class Event;

class Process
{

private:
	int pid;
	double *cpuBurst;/*This is an array of aow*/
	double *ioBurst;/*This is an array of times spent waiting*/
	int currentBurst;
	int nbBursts; /*This is the nb of cpu bursts. there qre n-1 io bursts.*/
	int priority;
public:
	Process(int p, int nbBursts, double *cpuBursts, double *ioBursts, int priority = 0);
	~Process();
	int getPid(void);
	void updateCurrentAow(double aow);
	bool advanceBurst();
	void decrementBurst();
	double getCurrentCpuAow();
	double getCurrentIoTime();
	static Process *createJob(int pid, double aow/*amount of work*/);
	static Process *createProcess(double cpuLambda, double ioLambda);
	static int getNewPid();
};










#endif
