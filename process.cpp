#include "process.h"
#include "randomGenerator.h"
#include <iostream>

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
	if (cpuBurst != nullptr)
		delete cpuBurst;
	if (ioBurst != nullptr)
		delete ioBurst;
}

int Process::getPid()
{
	return pid;
}


bool Process::advanceBurst()
{
	currentBurst++;
	return currentBurst < nbBursts;
}

void Process::decrementBurst()
{
	currentBurst--;
}

double Process::getCurrentCpuAow()
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


Process *Process::createJob(int pid, double aow)
{
	double *burst = new double;
	*burst = aow;
	Process *process = new Process(pid, 1, burst, nullptr);
	return process;
}


Process *Process::createProcess(double cpuLambda, double ioLambda)
{
	RandomGenerator *gen = RandomGenerator::getRandomGenerator();
	int nbBursts = 10;
	double *cpuBurst = new double[nbBursts];
	double *ioBurst = new double[nbBursts];
	for (int i = 0; i < nbBursts; i++)
	{
		cpuBurst[i] = gen->drawExp(cpuLambda);
		ioBurst[i] = gen->drawExp(ioLambda);
		std::cout << "cpuBurst["<<i<<"]: "<<cpuBurst[i]<<"\n";
		std::cout << "ioBurst["<<i<<"]: "<<ioBurst[i]<<"\n";
	}
	Process *p = new Process(Process::getNewPid(), nbBursts, cpuBurst, ioBurst);
	return p;
}




int Process::getNewPid()
{
	static int pid = 0;
	return pid++;
}



void Process::updateCurrentAow(double aow)
{
	cpuBurst[currentBurst] = aow;
}









