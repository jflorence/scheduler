#ifndef PRIORITYDISCIPLINE_H
#define PRIORITYDISCIPLINE_H

class PriorityDiscipline : SchedulingDiscipline
{
public:
	Process *selectNextTask(Queue *readyQueue, Process *running);
	virtual bool preempts(TriggeringEvent trigger);
	virtual std::string getName();
private:
};

#endif
