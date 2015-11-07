#ifndef RMSDISCIPLINE_H
#define RMSDISCIPLINE_H

#include <string>
#include "priorityDiscipline.h"

class RmsDiscipline : public PriorityDiscipline
{
public:

protected:
	virtual std::string getName() override;
	PriorityDiscipline::ComparatorPointer getComparator() override;
};

#endif
