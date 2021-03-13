#pragma once

#include "objects.h"
#include "Array.h"
#include "List.h"

struct Parameter
{
    enum PararamType{};
    PararamType type;
    double value;
};
class BasicInterface
{
public:
    BasicInterface();
    ID addObject(ObjType);
   /* ID addObject(ObjType, const Array<Parameter>&);*/
    bool removeObject(ID);
  /*  bool changeObjectProperty(ID);*/
    ID  addRequirement(Array<ID>&, ReqType);
    Array<Parameter>  queryObjPropertiesP(ID);
    Array<double>  queryObjProperties(ID);
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


