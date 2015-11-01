#ifndef EVENT_H
#define EVENT_H

class Process;
class EventList;

class Event
{

public:
	Event(double time, Process *task, bool renew = true);
	double getTime();
	/*FIXME I don't think the bool return is necessary*/
	virtual void process()=0;
	virtual ~Event();
protected:
	double time;
	Process *task;
	bool renew;
};



class NewProcess : public Event
{
public:
	NewProcess(double time, Process *task, bool renew=true) : Event(time, task, renew){};
	virtual void process()=0;
};

class NewInteractiveProcess : public NewProcess
{
public:
	NewInteractiveProcess(double time, Process *task, bool renew=true) : NewProcess(time, task, renew){};
	void process() override;
private:
	double lambda;
	Process *createTask();
	void queueProcess(Process *);
	void scheduleNextEvent();
};

class NewJob : public NewProcess
{
public:
	NewJob(double time, Process *task, bool renew=true) : NewProcess(time, task, renew){};
	void process() override;
};

class TimeOut : public Event
{
public:
	TimeOut(double time, Process *task, bool renew=true) : Event(time, task, renew){};
	void process() override;
	double getInterval();
	void setInterval(double inter);
private:
	double interval{2};
};

class Ready : public Event
{
public:
	Ready(double time, Process *task, bool renew=false) : Event(time, task, renew){};
	void process() override;
};

class Waiting : public Event
{
public:
	Waiting(double time, Process *task, bool renew=false) : Event(time, task, renew){};
	void process() override;
};

class Terminates : public Event
{
public:
	Terminates(double time, Process *task, bool renew=false) : Event(time, task, renew){};
	void process() override;
};

class StopSimulation : public Event
{
public:
	StopSimulation(double time, Process *task, bool renew=false) : Event(time, task, renew){};
	void process() override;
};



#endif












