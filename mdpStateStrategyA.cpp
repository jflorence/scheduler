#include "mdpStateStrategy.h"
#include "processor.h"
#include "queue.h"

mdpState MdpStateStrategyA::getState(Processor *proc, Queue *readyQueue, Queue *waitQueue)
{
	return readyQueue->size() + (proc->getFreq() > proc->getMinFreq() ? readyQueue->getMaxSize()+1 : 0);
}


