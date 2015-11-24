#ifndef QUEUE_H
#define QUEUE_H

#include <iterator>
#include <list>
#include <string>

class Process;

class Queue
{
public:
	static Queue *getReadyQueue();
	static Queue *getWaitQueue();
private:
	static Queue *readyQueue;
	static Queue *waitQueue;
public:
	void add(Process *p);
	Process *remove(Process *p);
	typedef std::list<Process *>::iterator iterator;
	iterator begin();
	iterator end();
	size_t size();
	bool isEmpty();
	void print();
	std::string getDisplay();
	int getMaxSize();
private:
	std::list<Process *> queue;
	std::string queueDisplay;
	const int maxSize{20};
};




#endif
