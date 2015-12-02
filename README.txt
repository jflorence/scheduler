TODO: put the mdp stuff in its own folder and namespace

TODO: solve the generator mess

TODO: overload the [] operator on the policy class

TODO: implement MDP scheduling


TODO: the processor's setBusy function should be able to be used when a process is running, in order to pause it

FIXME: find the right alpha for usage calculation
FIXME: find some realistic value for the temp coeffs


TODO: the action of the discipline depends on the event type. For the moment we use the eventType.h to take care of this.
A better solution would be maybe to have a visitor pattern (discipline=visitor, event=visited)
UPDATE: I don't think it's a good solution.
It would add a dependency of Event on SchedulingDiscipline. Also, SchedulingDiscipline would depend on Event,
but also we need as many visit() methods as there are event types (or at least types for wich the behavior differs from the default).
And this needs to be done for evey discipline.

