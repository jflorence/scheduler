TODO: the action of the discipline depends on the event type. For the moment we use the eventType.h to take care of this.
A better solution would be maybe to have a visitor pattern (discipline=visitor, event=visited)


TODO: make the color printing os independent
the << operator is a good solution, but we need a template...

FIXME: find the right alpha for usage calculation
FIXME: find some realistic value for he temp coeffs

TODO: move some information about power consumption in the processor class. Maybe reorganize Processor and TemperatureModel


TODO: implement MDP scheduling
