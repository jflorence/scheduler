
TODO: edf scheduling not yet working. I suspect deadlineTime is not set properly

TODO: the factoring of timeout can be improved. Create a virtual fct getNextTimeOut, and a virtual fct doWork().
then process() needs not be overriden



TODO: the action of the discipline depends on the event type. For the moment we use the eventType.h to take care of this.
A better solution would be maybe to have a visitor pattern (discipline=visitor, event=visited)

FIXME: FreqUpdate does not trigger anything? 

TODO: make the color printing os independent
TODO: indicate what is the seed used

FIXME: find the right alpha for usage calculation


TODO: move some information about power consumption in the processor class. Maybe reorganize Processor and TemperatureModel


TODO: implement MDP scheduling
