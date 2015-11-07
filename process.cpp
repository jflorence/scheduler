#include "process.h"
#include "randomGenerator.h"
#include <cassert>

Process::Process(int p, int nb, double *cpu, double *io, int pri)
{
	currentBurst = 0;
	pid = p;
	nbBursts = nb;
	cpuBurst = cpu;
	ioBurst = io;
	priority = pri;
}

Process::Process(const Process& task)
{
	currentBurst = 0;
	pid = task.pid;
	nbBursts = task.nbBursts;
	cpuBurst = new double[nbBursts];
	ioBurst = new double[nbBursts];
	for (int i = 0; i < nbBursts; i++)
	{
		cpuBurst[i] = task.cpuBurst[i];
		ioBurst[i] = task.ioBurst[i];
	}
	priority = task.priority;
	RT = task.RT;
	deadline = task.deadline;
	period = task.period;
	jobNumber = task.jobNumber;
}

Process::~Process()
{
	if (cpuBurst != nullptr)
	{
		delete[] cpuBurst;
		cpuBurst = nullptr;
	}
	if (ioBurst != nullptr)
	{
		delete[] ioBurst;
		ioBurst = nullptr;
	}
}

int Process::getPid()
{
	return pid;
}

int Process::getPriority()
{
	return priority;
}

void Process::setPriority(int pri)
{
	priority = pri;
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
	assert(cpuBurst != nullptr);
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
	}
	Process *p = new Process(Process::getNewPid(), nbBursts, cpuBurst, ioBurst);
	return p;
}

Process *Process::createRealTimeTask(double aow, double T, double dl, int pid, double dlTime)
{
	int nbBursts = 1;
	double *cpuBurst = new double[nbBursts];
	double *ioBurst = new double[nbBursts];
	cpuBurst[0] = aow;
	ioBurst[0] = 0;
	Process *p = new Process(pid, nbBursts, cpuBurst, ioBurst);
	p->setRtParams(dl, T, dlTime);
	return p;
}

void Process::setRtParams(double dl, double T, double dlTime)
{
	deadline = dl;
	period = T;
	RT = true;
	deadlineTime = dlTime;
}

double Process::getDeadline()
{
	return deadline;
}

void Process::setDeadlineTime(double dlTime)
{
	deadlineTime = dlTime;
}

bool Process::isRealTime()
{
	return RT;
}

int Process::getNewPid()
{
	static int pid = 0;
	return pid++;
}



void Process::updateCurrentAow(double aow)
{
	assert(cpuBurst != nullptr);
	cpuBurst[--currentBurst] = aow;
}

double Process::getPeriod()
{
	return period;
}

double Process::getDeadlineTime()
{
	return deadlineTime;
}

void Process::print(std::ostream& stream)
{
	stream << "Processs "<<pid<<":\n";
	stream << "    priority: "<<priority<<"\n";
	stream << "    Bursts:\n";
	for (int i = 0; i < nbBursts; i++)
	{
		stream << "      "<<i<<". CPU: "<<cpuBurst[i]<<"\n";
		stream << "                        IO: " <<ioBurst[i]<<"\n";
	}
	if (RT)
	{
		stream << "    This proces IS real-time\n";
		stream << "    Deadline: "<<deadline<<"\n";
		stream << "    Period: "<<period<<"\n";
	}
	else
	{
		stream << "    This process IS NOT real-time\n";
	}
	stream << "\n";
}


void Process::incrementJobNumber()
{
	jobNumber++;
}

unsigned int Process::getJobNumber()
{
	return jobNumber;
}














