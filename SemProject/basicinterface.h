#pragma once

#include "objects.h"
#include "Array.h"
#include "List.h"

struct Parameter
{
    enum ParamType
    {
        PT_ERROR,
        PT_POINT,
        PT_CIRCLE,
        PT_SEGMENT,
        PT_CX,
        PT_CY,
        PT_R,
        PT_P1X,
        PT_P2X,
        PT_P1Y,
        PT_P2Y,
        PT_PX,
        PT_PY
    };
    ParamType type;
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
    Array<Parameter> queryObjProperties(ID);
    ObjType identifyObjTypeByID(ID);
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


