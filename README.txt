TODO singletons should have a private class

TODO allow mdp to print status

TODO: modify makefile so that changes to .h rebuilds the .cpp

TODO: what to do in case of "full" ready/wait queue?

TODO: solve the generator mess


TODO: implement MDP scheduling
TODO: Use a configuration file to select governor, policy, discipline, etc

TODO: the processor's setBusy function should be able to be used when a process is running, in order to pause it

TODO: overload the [] operator on the policy class
FIXME: find the right alpha for usage calculation
FIXME: find some realistic value for the temp coeffs


TODO: the action of the discipline depends on the event type. For the moment we use the eventType.h to take care of this.
A better solution would be maybe to have a visitor pattern (discipline=visitor, event=visited)
UPDATE: I don't think it's a good solution.
It would add a dependency of Event on SchedulingDiscipline. Also, SchedulingDiscipline would depend on Event,
but also we need as many visit() methods as there are event types (or at least types for wich the behavior differs from the default).
And this needs to be done for evey discipline.

