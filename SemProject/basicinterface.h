#pragma once

#include "objects.h"
#include "Array.h"
#include "List.h"


class BasicInterface
{
public:
    BasicInterface();
    ID addObject(ObjType);
    bool removeObject(ID);
    bool changeObjectProperty(ID);
    ID  addRequirement(Array<ID>&, ReqType);
    // TODO 
    // queryObjProperties(ID) ???

    bool removeRequirement(ID);

private:
    Array<Identifiable<Point> > m_points;
    Array<Identifiable<Segment> > m_segments;
    Array<Identifiable<Circle> > m_circles;

    List<Identifiable<Point>> l_points;
    List<Identifiable<Segment>> l_segmentss;
    List<Identifiable<Circle>> l_circles;

    Array<Identifiable<Requirement> > m_requirements;
};


