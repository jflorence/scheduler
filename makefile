CC = g++
CPPFLAGS = -g -W -Wall -std=c++11
LDFLAGS = 

all: scheduler

scheduler: main.o event.o eventList.o process.o queue.o randomGenerator.o taskScheduler.o fcfsDiscipline.o roundRobinDiscipline.o simpleTemperatureModel.o maxGovernor.o minGovernor.o conservativeGovernor.o processor.o
	$(CC) $(CFLAGS) -o scheduler main.o event.o eventList.o process.o queue.o randomGenerator.o taskScheduler.o fcfsDiscipline.o roundRobinDiscipline.o simpleTemperatureModel.o maxGovernor.o minGovernor.o conservativeGovernor.o processor.o

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
maxGovernor.o: maxGovernor.cpp
minGovernor.o: minGovernor.cpp
conservativeGovernor.o: conservativeGovernor.cpp
processor.o: processor.cpp

clean:
	rm -f ./scheduler
	rm -f *.o
	rm -f processes.txt
	rm -f reports.txt
