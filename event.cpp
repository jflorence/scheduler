#include "event.h"
#include <iostream>
#include "process.h"
#include "log.h"

Event::Event(double t, Process *p, bool r)
{
	time = t;
	task = p;
	renew = r;
}

double Event::getTime()
{
	return time;
}


bool StopSimulation::process(EventList *list)
{
	log(this, "Simulation stopped");
	return false;
}

bool NewInteractiveProcess::process(EventList *list)
{
/*TODO*/
	Process *process = Process::createJob(1, time, 50);
	log(this, "process "<<process->getPid()<<" created");
	return true;
}

bool NewJob::process(EventList *list)
{
/*TODO*/
	return true;
}

bool TimeOut::process(EventList *list)
{
/*TODO*/
	return true;
}

bool Ready::process(EventList *list)
{
/*TODO*/
	return true;
}

bool Waiting::process(EventList *list)
{
/*TODO*/
	return false;
}

bool Terminates::process(EventList *list)
{
/*TODO*/
	return false;
}









