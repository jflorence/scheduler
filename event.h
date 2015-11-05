#ifndef EVENT_H
#define EVENT_H

#include "eventType.h"

class Process;
class EventList;

class Event
{

public:
	Event(double time, Process *task, bool renew = true);
	double getTime();
	virtual void process()=0;
	virtual ~Event();
	virtual void print()=0;
protected:
	double time;
	bool renew;
	Process *task;
	TriggeringEvent eventType;
};



class NewProcess : public Event
{
public:
	NewProcess(double time, Process *task, bool renew=true) : Event(time, task, renew){eventType=newprocess;};
	virtual ~NewProcess();
	virtual void process()=0;
	virtual void print()=0;
protected:
	void queueProcess(Process *p);
	virtual void scheduleNextEvent()=0;
	virtual Process *createTask()=0;
};

class NewInteractiveProcess : public NewProcess
{
public:
	NewInteractiveProcess(double time, Process *task, bool renew=true) : NewProcess(time, task, renew){};
	void process() override;
	void print() override;
private:
	double lambda;
	Process *createTask() override;
	void scheduleNextEvent() override;
};

class NewJob : public NewProcess
{
public:
	NewJob(double time, Process *task, bool renew=true) : NewProcess(time, task, renew){};
	void process() override;
	void print() override;
private:
	Process *createTask() override;
	void scheduleNextEvent() override;
	int pid{-1};
};

class TimeOut : public Event
{
public:
	TimeOut(double time, Process *task, bool renew=true) : Event(time, task, renew){eventType=timeout;};
	virtual void process() override;
	double getInterval();
	void setInterval(double inter);
	virtual void print() override;
	void setType(TriggeringEvent trigger);
protected:
	double interval{2};
};

class UsageUpdate : public TimeOut
{
public:
	UsageUpdate(double time, Process *task, bool renew=true) : TimeOut(time, task, renew){eventType=usageUpdate;};
	void process() override;
	void print() override;
};

class Ready : public Event
{
public:
	Ready(double time, Process *task, bool renew=false) : Event(time, task, renew){eventType=ready;};
	void process() override;
	void print() override;
};

class Waiting : public Event
{
public:
	Waiting(double time, Process *task, bool renew=false) : Event(time, task, renew){eventType=wait;};
	void process() override;
	void print() override;
};

class Terminates : public Event
{
public:
	Terminates(double time, Process *task, bool renew=false) : Event(time, task, renew){eventType=terminate;};
	void process() override;
	void print() override;
};

class StopSimulation : public Event
{
public:
	StopSimulation(double time, Process *task, bool renew=false) : Event(time, task, renew){eventType=stop;};
	void process() override;
	void print() override;
};



#endif












