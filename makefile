CC = g++
CPPFLAGS = -g -W -Wall -std=c++11
LDFLAGS = 

all: scheduler

scheduler: main.o event.o eventList.o process.o queue.o randomGenerator.o taskScheduler.o fcfsDiscipline.o roundRobinDiscipline.o simpleTemperatureModel.o
	$(CC) $(CFLAGS) -o scheduler main.o event.o eventList.o process.o queue.o randomGenerator.o taskScheduler.o fcfsDiscipline.o roundRobinDiscipline.o simpleTemperatureModel.o

main.o: main.cpp
event.o: event.cpp
eventList.o: eventList.cpp
process.o: process.cpp
queue.o: queue.cpp
randomGenerator.o: randomGenerator.cpp
taskScheduler.o: taskScheduler.cpp
fcfsDiscipline.o: fcfsDiscipline.cpp
roundRobinDiscipline.o: roundRobinDiscipline.cpp
simpleTemperatureModel.o: simpleTemperatureModel.cpp




clean:
	rm ./scheduler
