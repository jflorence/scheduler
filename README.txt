

FIXME: find the right alpha for usage calculation
FIXME: find some realistic value for the temp coeffs


TODO: the action of the discipline depends on the event type. For the moment we use the eventType.h to take care of this.
A better solution would be maybe to have a visitor pattern (discipline=visitor, event=visited)
UPDATE: I don't think it's a good solution.
It would add a dependency of Event on SchedulingDiscipline. Also, SchedulingDiscipline would depend on Event,
but also we need as many visit() methods as there are event types (or at least types for wich the behavior differs from the default).
And this needs to be done for evey discipline.

TODO: implement MDP scheduling
