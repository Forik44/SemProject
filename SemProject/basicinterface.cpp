#pragma once
#include "basicinterface.h"
#include <iostream>

BasicInterface::BasicInterface()
{

};

ID  BasicInterface::addObject(ObjType ot)
{
    ID id = ID::generateID();
    switch (ot) {
    case OT_POINT:
        m_points.add({ id,Point() });
        break;
    case OT_SEGMENT:
        m_segments.add({ id,Segment() });
        break;
    case OT_CIRCLE:
        m_circles.add({ id,Circle() });
        break;
    }
    return id;

};
bool BasicInterface::removeObject(ID id) {
    for (size_t k = 0; k < m_points.getSize();++k) {
        if (m_points[k].id == id) {
            m_points.removeElementByIdx(k);
            return true;
        }
    }
    for (size_t k = 0; k < m_segments.getSize();++k) {
        if (m_segments[k].id == id) {
            m_segments.removeElementByIdx(k);
            return true;
        }
    }
    for (size_t k = 0; k < m_circles.getSize();++k) {
        if (m_circles[k].id == id) {
            m_circles.removeElementByIdx(k);
            return true;
        }
    }
    return false;
};
ID  BasicInterface::addRequirement(Array<ID>&, ReqType rt) {
    ID id = ID::generateID();
    switch (rt) {
    case RT_PARALLEL:
        break;
    case RT_ORTHO:
        break;
    case RT_COINCIDE:
        break;
    case RT_GROUP:
        break;
    case RT_DISTANCE:
        break;
    }
    return id;
};
bool BasicInterface::removeRequirement(ID id) {
    for (size_t k = 0; k < m_requirements.getSize();++k) {
        if (m_requirements[k].id == id) {
            m_requirements.removeElementByIdx(k);
            return true;
        }
    }
    return false;
};
//Array<Parameter>  BasicInterface::queryObjPropertiesP(ID id)
//{

//}
ObjType BasicInterface::identifyObjTypeByID(ID id)
{
    Array<Identifiable<Point> >::Marker pm = m_points.init();
    while (pm != m_points.afterEnd())
    {
        if ((*pm).id == id)
            return OT_POINT;
        pm++;
    };
    Array<Identifiable<Circle> >::Marker cm = m_circles.init();
    while (cm != m_circles.afterEnd())
    {
        if ((*cm).id == id)
            return OT_CIRCLE;
        cm++;
    }
    Array<Identifiable<Segment> >::Marker sm = m_segments.init();
    while (sm != m_segments.afterEnd())
    {
        if ((*sm).id == id)
            return OT_CIRCLE;
        sm++;
    }
   
}

