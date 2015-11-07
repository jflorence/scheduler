#include "edfDiscipline.h"

#include <algorithm>
#include "process.h"

std::string EdfDiscipline::getName()
{
	return "Earliest Deadline First Discipline";
}


PriorityDiscipline::ComparatorPointer EdfDiscipline::getComparator()
{
	return [](Process *a, Process *b){return a->getDeadlineTime() < b->getDeadlineTime();};
}
