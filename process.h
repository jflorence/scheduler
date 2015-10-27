#ifndef PROCESS_H
#define PROCESS_H

#include "event.h"


class Process
{

private:
	int pid;
	/*the bursts are arrays of times spent in the nth burst*/
	double *cpuBurst;
	double *ioBurst;
	int currentBurst;
	int nbBursts; /*This is the nb of cpu bursts. there qre n-1 io bursts.*/
	int priority;
	static int pidCounter;
public:
	Process(int p, int nbBursts, double *cpuBursts, double *ioBursts, int priority = 0);
	~Process();
	int getPid(void);
	void updateBurstTime(double time);
	bool advanceBurst();
	double getCurrentCpuTime();
	double getCurrentIoTime();
	static Process *createJob(int pid, double time, double aow/*amount of work*/);	
};










#endif
