#include "schedulingDiscipline.h"

bool SchedulingDiscipline::doesPreempt(Visited *v)
{
	v->accept(this);
	return preempts;
}



