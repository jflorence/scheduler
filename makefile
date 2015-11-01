scheduler: main.cpp
	g++ -o scheduler main.cpp event.cpp eventList.cpp process.cpp queue.cpp randomGenerator.cpp taskScheduler.cpp fcfsDiscipline.cpp roundRobinDiscipline.cpp -g -Wall -std=c++11



clean:
	rm ./scheduler
