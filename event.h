#ifndef EVENT_H
#define EVENT_H

class Process;

class Event
{

private:
	double time;
	Process *process;
	enum eventType {NewProcess, TimeOut, Ready, Waiting, Terminates, StopSimulation};
public:


};



#endif












