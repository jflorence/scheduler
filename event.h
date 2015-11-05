#ifndef EVENT_H
#define EVENT_H

#include "eventType.h"
#include <string>

class Process;
class EventList;

class Event
{

public:
	Event(double time, Process *task=nullptr, bool renew = true);
	double getTime();
	virtual void process()=0;
	virtual ~Event();
	void print();
	virtual std::string getName()=0;
protected:
	double time;
	bool renew;
	Process *task{nullptr};
	TriggeringEvent eventType;
};



class NewProcess : public Event
{
public:
	NewProcess(double time, Process *task=nullptr, bool renew=true) : Event(time, task, renew){eventType=newprocess;};
	virtual ~NewProcess();
	virtual void process()=0;
	virtual std::string getName()=0;
protected:
	void queueProcess(Process *p);
	virtual void scheduleNextEvent()=0;
	virtual Process *createTask()=0;
};

class NewInteractiveProcess : public NewProcess
{
public:
	NewInteractiveProcess(double time, Process *task=nullptr, bool renew=true) : NewProcess(time, task, renew){};
	void process() override;
	std::string getName() override;
private:
	double lambda;
	Process *createTask() override;
	void scheduleNextEvent() override;
};

class NewJob : public NewProcess
{
public:
	NewJob(double time, Process *task=nullptr, bool renew=true) : NewProcess(time, task, renew){};
	void process() override;
	std::string getName() override;
private:
	Process *createTask() override;
	void scheduleNextEvent() override;
	int pid{-1};
};

class TimeOut : public Event
{
public:
	TimeOut(double time, Process *task=nullptr, bool renew=true) : Event(time, task, renew){eventType=timeout;};
	virtual void process() override;
	double getInterval();
	void setInterval(double inter);
	virtual std::string getName() override;
protected:
	double interval{2};
};

class UsageUpdate : public TimeOut
{
public:
	UsageUpdate(double time, Process *task=nullptr, bool renew=true) : TimeOut(time, task, renew){eventType=usageUpdate;};
	void process() override;
	std::string getName() override;
};

class FreqUpdate : public TimeOut
{
public:
	FreqUpdate(double time, Process *task=nullptr, bool renew=true) : TimeOut(time, task, renew){eventType=freqUpdate;};
	void process();
	std::string getName();
};

class Ready : public Event
{
public:
	Ready(double time, Process *task=nullptr, bool renew=false) : Event(time, task, renew){eventType=ready;};
	void process() override;
	std::string getName() override;
};

class Waiting : public Event
{
public:
	Waiting(double time, Process *task=nullptr, bool renew=false) : Event(time, task, renew){eventType=wait;};
	void process() override;
	std::string getName() override;
};

class Terminates : public Event
{
public:
	Terminates(double time, Process *task=nullptr, bool renew=false) : Event(time, task, renew){eventType=terminate;};
	void process() override;
	std::string getName() override;
};

class StopSimulation : public Event
{
public:
	StopSimulation(double time, Process *task=nullptr, bool renew=false) : Event(time, task, renew){eventType=stop;};
	void process() override;
	std::string getName() override;
};



#endif












