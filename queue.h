#ifndef QUEUE_H
#define QUEUE_H

#include <list>
#include <iterator>
class Process;

class Queue
{

public:
	static Queue *getReadyQueue();
	static Queue *getWaitQueue();
	void add(Process *p);
	Process *remove(Process *p);
	typedef std::list<Process *>::iterator iterator;
	iterator begin();
	iterator end();
	size_t size();
	bool isEmpty();
	void print();
private:
	std::list<Process *> queue;
	static Queue *readyQueue;
	static Queue *waitQueue;
};




#endif
