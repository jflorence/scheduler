CC = g++
CPPFLAGS = -g -W -Wall -std=c++11
LDFLAGS = 
OBJ = main.o event.o eventList.o process.o queue.o randomGenerator.o taskScheduler.o fcfsDiscipline.o roundRobinDiscipline.o simpleTemperatureModel.o maxGovernor.o minGovernor.o conservativeGovernor.o processor.o priorityDiscipline.o rmsDiscipline.o schedulingSimulator.o edfDiscipline.o log.o system.o fixedPriorityDiscipline.o mdpGovernor.o mdpStateSpace.o mdpTransitionMatrix.o mdpPolicy.o mdpRewards.o mdpAction.o mdpStateSpaceDimension.o

all: scheduler

scheduler: $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o scheduler

main.o: main.cpp log.h
event.o: event.cpp log.h
eventList.o: eventList.cpp log.h
process.o: process.cpp log.h
queue.o: queue.cpp log.h
randomGenerator.o: randomGenerator.cpp log.h
taskScheduler.o: taskScheduler.cpp log.h
fcfsDiscipline.o: fcfsDiscipline.cpp log.h
roundRobinDiscipline.o: roundRobinDiscipline.cpp log.h
simpleTemperatureModel.o: simpleTemperatureModel.cpp log.h
maxGovernor.o: maxGovernor.cpp log.h
minGovernor.o: minGovernor.cpp log.h
conservativeGovernor.o: conservativeGovernor.cpp log.h
processor.o: processor.cpp log.h
priorityDiscipline.o: priorityDiscipline.cpp log.h
Rmsdiscipline.o: rmsDiscipline.cpp log.h
schedulingSimulator.o: schedulingSimulator.cpp log.h
edfDiscipline.o: edfDiscipline.cpp log.h
log.o: log.cpp log.h
system.o: system.cpp log.h
fixedPriorityDiscipline.o: fixedPriorityDiscipline.cpp log.h
mdpGovernor.o: mdpGovernor.cpp log.h
mdpStateSpace.o: mdpStateSpace.cpp log.h
mdpPolicy.o: mdpPolicy.cpp log.h
mdpRewards.o: mdpRewards.cpp log.h
mdpTransitionMatrix.o: mdpTransitionMatrix.cpp log.h
mdpAction.o: mdpAction.cpp log.h
mdpStateSpaceDimension.o: mdpStateSpaceDimension.cpp log.h

clean:
	rm -f ./scheduler
	rm -f *.o
	rm -f processes.txt
	rm -f reports.txt
