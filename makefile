CC = g++
CXXFLAGS = -g -W -Wall -std=c++11
LDFLAGS = 

sources :=
programs := scheduler
objects = $(subst .cpp,.o,$(sources))
 

RM := rm -f


sources += conservativeGovernor.cpp
sources += edfDiscipline.cpp
sources += event.cpp
sources += eventList.cpp
sources += fcfsDiscipline.cpp
sources += fixedPriorityDiscipline.cpp
sources += log.cpp
sources += main.cpp
sources += maxGovernor.cpp
sources += mdpGovernor.cpp
sources += minGovernor.cpp
sources += priorityDiscipline.cpp
sources += process.cpp
sources += processor.cpp
sources += queue.cpp
sources += randomGenerator.cpp
sources += rmsDiscipline.cpp
sources += roundRobinDiscipline.cpp
sources += schedulingSimulator.cpp
sources += simpleTemperatureModel.cpp
sources += system.cpp
sources += taskScheduler.cpp





all:

include mdp/module.mk


.PHONY: all
all: $(programs)

.PHONY: clean
clean:
	$(RM) $(objects) $(programs)
	$(RM) processes.txt reports.txt








scheduler: $(objects) 
	$(CC) $(CXXFLAGS) $(CPPFLAGS) $(objects) -o scheduler


