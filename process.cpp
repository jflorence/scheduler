#include "process.h"




Process::Process(int p, int nb, double *cpu, double *io, int pri)
{
	currentBurst = 0;
	pid = p;
	nbBursts = nb;
	cpuBurst = cpu;
	ioBurst = io;
	priority = pri;
}

Process::~Process()
{
	delete cpuBurst;
	delete ioBurst;
}




int Process::getPid()
{
	return pid;
}


void Process::updateBurstTime(double t)
{
	cpuBurst[currentBurst] = t;
}

bool Process::advanceBurst()
{
	currentBurst++;
	return currentBurst <= nbBursts;
}


double Process::getCurrentCpuTime()
{
	return cpuBurst[currentBurst];
}

double Process::getCurrentIoTime()
{
	if (nbBursts > currentBurst && ioBurst != nullptr)
		return ioBurst[currentBurst];
	else
		return -1;
}




Process *Process::createJob(int pid, double time, double aow)
{
	double *burst = new double;
	*burst = aow;
	Process *process = new Process(pid, 1, burst, nullptr);
	return process;
}







