TODO: make the accept() in Event pure virtual

Actually, we can make accept virtual in event,
visit virtual in all non-leaf disciplines, and have a visit(Event) defined in every leaf

TODO: The BIGISSUE could be maybe solved with the acyclic visitor pattern. However, this brings us back to the original solution, only in much more complicated. It is therefore not a solution.
Also look at partial visitation

TODO: classes with virtual functions need a virtual destructor
TODO: "A class with any of {destructor, copy assignment operator, copy constructor, move assignment operator, move constructor} generally needs all 5" https://isocpp.org/wiki/faq/coding-standards

TODO: move the scheduling timeout in its own derived class
TODO: Same for fixed priority

FIXME: find the right alpha for usage calculation
FIXME: find some realistic value for the temp coeffs


TODO: the action of the discipline depends on the event type. For the moment we use the eventType.h to take care of this.
A better solution would be maybe to have a visitor pattern (discipline=visitor, event=visited)
UPDATE: I don't think it's a good solution.
It would add a dependency of Event on SchedulingDiscipline. Also, SchedulingDiscipline would depend on Event,
but also we need as many visit() methods as there are event types (or at least types for wich the behavior differs from the default).
And this needs to be done for evey discipline.

TODO: implement MDP scheduling
