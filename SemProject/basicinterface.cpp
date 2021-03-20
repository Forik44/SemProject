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
ID  BasicInterface::addRequirement(const Array<ID>& id, ReqType rt) {
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
Array<Parameter> BasicInterface::queryObjProperties(ID id)
{
    switch (identifyObjTypeByID(id))
    {
    case OT_CIRCLE:
    {
        Array<Identifiable<Circle> >::Marker cm = m_circles.init();
        while ((*cm).id != id)
            cm++;
        Array<Parameter> arr;
        Parameter obj;

        obj.type = Parameter::PT_CIRCLE;
        obj.value = 4;
        arr.add(obj);

        obj.type = Parameter::PT_CX;
        obj.value = (*cm).obj.center.x;
        arr.add(obj);

        obj.type = Parameter::PT_CY;
        obj.value = (*cm).obj.center.y;
        arr.add(obj);

        obj.type = Parameter::PT_R;
        obj.value = (*cm).obj.r;
        arr.add(obj);

        return arr;
        break;
    }
    case OT_POINT:
    {
        Array<Identifiable<Point> >::Marker pm = m_points.init();
        while (pm != m_points.afterEnd())
            pm++;

        Array<Parameter> arr;
        Parameter obj;

        obj.type = Parameter::PT_POINT;
        obj.value = 3;
        arr.add(obj);

        obj.type = Parameter::PT_PX;
        obj.value = (*pm).obj.x;
        arr.add(obj);

        obj.type = Parameter::PT_PY;
        obj.value = (*pm).obj.y;
        arr.add(obj);

        return arr;
        break;

    }
    case OT_SEGMENT:
    {
        Array<Identifiable<Segment> >::Marker sm = m_segments.init();
        while (sm != m_segments.afterEnd())
            sm++;

        Array<Parameter> arr;
        Parameter obj;

        obj.type = Parameter::PT_SEGMENT;
        obj.value = 5;
        arr.add(obj);

        obj.type = Parameter::PT_P1X;
        obj.value = (*sm).obj.p1.x;
        arr.add(obj);

        obj.type = Parameter::PT_P1Y;
        obj.value = (*sm).obj.p1.y;
        arr.add(obj);

        obj.type = Parameter::PT_P2X;
        obj.value = (*sm).obj.p2.x;
        arr.add(obj);

        obj.type = Parameter::PT_P1X;
        obj.value = (*sm).obj.p2.y;
        arr.add(obj);

        return arr;

        break;
    }
    case OT_ERROR:
    {
        Array<Parameter> arr;
        Parameter err;
        err.type = Parameter::PT_ERROR;
        arr.add(err);
        return arr;
    }
    }
}
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
    return OT_ERROR;
}

