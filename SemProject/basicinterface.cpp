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
Parameter* BasicInterface::queryObjProperties(ID id)
{
    switch (identifyObjTypeByID(id))
    {
    case OT_CIRCLE:
    {
        Array<Identifiable<Circle> >::Marker cm = m_circles.init();
        while ((*cm).id != id)
            cm++;
        Parameter* ptr = new Parameter[4];
        Parameter cx, cy, r, obj;

        obj.type = Parameter::PT_CIRCLE;
        obj.value = 4;
        ptr[0] = obj;

        cx.type = Parameter::PT_CX;
        cx.value = (*cm).obj.center.x;
        ptr[1] = cx;

        cy.type = Parameter::PT_CY;
        cy.value = (*cm).obj.center.y;
        ptr[2] = cy;

        r.type = Parameter::PT_R;
        r.value = (*cm).obj.r;
        ptr[3] = r;

        return ptr;
        break;
    }
    case OT_POINT:
    {
        Array<Identifiable<Point> >::Marker pm = m_points.init();
        while (pm != m_points.afterEnd())
            pm++;

        Parameter* ptr = new Parameter[2];
        Parameter x, y, obj;

        obj.type = Parameter::PT_POINT;
        obj.value = 3;
        ptr[0] = obj;

        x.type = Parameter::PT_PX;
        x.value = (*pm).obj.x;
        ptr[1] = x;

        y.type = Parameter::PT_PY;
        y.value = (*pm).obj.y;
        ptr[2] = y;

        return ptr;
        break;

    }
    case OT_SEGMENT:
    {
        Array<Identifiable<Segment> >::Marker sm = m_segments.init();
        while (sm != m_segments.afterEnd())
            sm++;

        Parameter* ptr = new Parameter[5];
        Parameter p1x, p1y, p2x, p2y, obj;

        obj.type = Parameter::PT_SEGMENT;
        obj.value = 5;
        ptr[0] = obj;

        p1x.type = Parameter::PT_P1X;
        p1x.value = (*sm).obj.p1.x;
        ptr[1] = p1x;

        p1y.type = Parameter::PT_P1Y;
        p1y.value = (*sm).obj.p1.y;
        ptr[2] = p1y;

        p2x.type = Parameter::PT_P2X;
        p2x.value = (*sm).obj.p2.x;
        ptr[3] = p2x;

        p2y.type = Parameter::PT_P1X;
        p2y.value = (*sm).obj.p2.y;
        ptr[4] = p2y;

        return ptr;

        break;
    }
    default:
        return nullptr;
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
   
}

