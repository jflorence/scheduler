#include "queue.h"
#include "process.h"
#include <cassert>
#include <iostream>
#include <sstream>

Queue *Queue::readyQueue = nullptr;
Queue *Queue::waitQueue = nullptr;

void Queue::add(Process *p)
{
	for (auto it = queue.begin(); it != queue.end(); it++)
	{
		//assert(p != (*it));
	}

	queue.push_back(p);
	assert(p != nullptr);
}


Queue *Queue::getReadyQueue()
{
	if (!readyQueue)
		readyQueue = new Queue;
	return readyQueue;
}

Queue *Queue::getWaitQueue()
{
	if (!waitQueue)
		waitQueue = new Queue;
	return waitQueue;
}


Process *Queue::remove(Process *p)
{
	if (p == nullptr)
		return nullptr;
	for (auto it = queue.begin(); it != queue.end(); it++)
	{
		if ((*it) == p)
		{
			queue.remove(p);
			return (p);
		}
	}
	assert(0 == 1);
	return nullptr;/*Should not happen*/
}



Queue::iterator Queue::begin()
{
	return queue.begin();
}
Queue::iterator Queue::end()
{
	return queue.end();
}


size_t Queue::size()
{
	return queue.size();
}

bool Queue::isEmpty()
{
	return (size() == 0);
}


void Queue::print()
{
	std::cout << "The queue contains:\n";
	for (auto it = queue.begin(); it != queue.end(); it++)
	{
		std::cout << "    pid "<<(*it)->getPid()<<"\n";
	}
}

std::string Queue::getDisplay()
{
	if (queue.empty())
	{
		return "nothing";
	}
	std::ostringstream stream;
	for (auto it = queue.begin(); it != queue.end(); it++)
	{
		stream << (*it)->getPid() << " ";
	}
	return stream.str();
}














