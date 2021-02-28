#ifndef BASICINTERFACE_H
#define BASICINTERFACE_H
#include "objects.h"
#include "Array.h"


class BasicInterface
{
public:
    BasicInterface();
    ID addObject(ObjType);
    bool removeObject(ID );
    bool changeObjectProperty(ID);
    ID  addRequirement(Array<ID>&, ReqType);

    bool removeRequirement(ID);
private:
    Array<Identifiable<Point> > m_points;
    Array<Identifiable<Segment> > m_segments;
    Array<Identifiable<Circle> > m_circles;

    Array<Identifiable<Requirement> > m_requirements;
};

#endif // BASICINTERFACE_H
