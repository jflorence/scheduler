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
	virtual bool process(EventList *list)=0;
protected:
	double time;
	Process *task;
	bool renew;
};



class NewProcess : public Event
{
public:
	NewProcess(double time, Process *task, bool renew=true) : Event(time, task, renew){};
	virtual bool process(EventList *list)=0;
};

class NewInteractiveProcess : public NewProcess
{
public:
	NewInteractiveProcess(double time, Process *task, bool renew=true) : NewProcess(time, task, renew){};
	bool process(EventList *list) override;
private:
};

class NewJob : public NewProcess
{
public:
	bool process(EventList *list) override;
};

class TimeOut : public Event
{
public:
	bool process(EventList *list) override;
};

class Ready : public Event
{
public:
	bool process(EventList *list) override;
};

class Waiting : public Event
{
public:
	bool process(EventList *list) override;
};

class Terminates : public Event
{
public:
	bool process(EventList *list) override;
};

class StopSimulation : public Event
{
public:
	StopSimulation(double time, Process *task, bool renew=true) : Event(time, task, renew){};
	bool process(EventList *list) override;
};



#endif












