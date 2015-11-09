#ifndef PROCESS_H
#define PROCESS_H

#include <iterator>
#include <cmath>
#include <ostream>

class Event;

class Process
{
public:
	static Process *createJob(int pid, double aow/*amount of work*/);
	static Process *createProcess(double cpuLambda, double ioLambda);
	static Process *createRealTimeTask(double aow, double T, double dl, int pid, double dlTime);
	static int getNewPid();
	
	Process(int p, int nbBursts, double *cpuBursts, double *ioBursts, int priority = 0);
	Process(const Process& task);
	~Process();
	
	int getPid(void);
	int getPriority();
	void setPriority(int pri);
	void updateCurrentAow(double aow);
	bool advanceBurst();
	void decrementBurst();
	double getCurrentCpuAow();
	double getCurrentIoTime();
	void setRtParams(double dl, double T, double dlTime);
	bool isRealTime();
	double getPeriod();
	double getDeadline();
	double getDeadlineTime();
	void setDeadlineTime(double dlTime);
	void print(std::ostream& stream);
	void incrementJobNumber();
	unsigned int getJobNumber();
	const double powerCoeff{1.0};
private:
	int pid;
	double *cpuBurst;/*This is an array of aow*/
	double *ioBurst;/*This is an array of times spent waiting*/
	int currentBurst{0};
	int nbBursts; /*This is the nb of cpu bursts. there qre n-1 io bursts.*/
	int priority{0};

	/*Those are the real time parameters. Maybe would it be better to put them in an aggregated class*/
	bool RT{false};
	double deadline{INFINITY};
	double deadlineTime{0.0};
	double period{INFINITY};
	unsigned int jobNumber{0};
};







#endif
