#ifndef VISITOR_H
#define VISITOR_H

class Visited;

class Visitor
{
public:
	virtual void visit(Visited *visited)=0;
};


#endif
