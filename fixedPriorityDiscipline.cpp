#include "fixedPriorityDiscipline.h"

std::string FixedPriorityDiscipline::getName()
{
	return "Fixed priority";
}

void FixedPriorityDiscipline::updatePriorities(Queue *, Process *)
{
	/*note that this redefinition is not necessary, as the default PriorityDiscipline already
	implements a fixed priority. This redefinition is an optimization.*/
	return;
}


