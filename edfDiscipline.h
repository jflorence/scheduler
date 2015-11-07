#ifndef EDFDISCIPLINE_H
#define EDFDISCIPLINE_H

#include <string>
#include "priorityDiscipline.h"

class EdfDiscipline : public PriorityDiscipline
{
public:

protected:
	virtual std::string getName();
	PriorityDiscipline::ComparatorPointer getComparator() override;
};

#endif
