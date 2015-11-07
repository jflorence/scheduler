#include "rmsDiscipline.h"

#include <algorithm>
#include "process.h"


std::string RmsDiscipline::getName()
{
	return "Rate Monotonic Scheduling Discipline";
}


PriorityDiscipline::ComparatorPointer RmsDiscipline::getComparator()
{
	return [](Process *a, Process *b){return a->getPeriod() < b->getPeriod();};
}














