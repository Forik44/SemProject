#pragma once
#include "basicinterface.h"

BasicInterface::BasicInterface()
{

};

ID  BasicInterface::addObject(ObjType ot)
{
    ID id;
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
        if (m_points.getElementByIdx(k).id.isEqual(id)) {
            m_points.removeElementByIdx(k);
            return true;
        }
    }
    for (size_t k = 0; k < m_segments.getSize();++k) {
        if (m_segments.getElementByIdx(k).id.isEqual(id)) {
            m_segments.removeElementByIdx(k);
            return true;
        }
    }
    for (size_t k = 0; k < m_circles.getSize();++k) {
        if (m_circles.getElementByIdx(k).id.isEqual(id)) {
            m_circles.removeElementByIdx(k);
            return true;
        }
    }
    return false;
};

ID  BasicInterface::addRequirement(Array<ID>&, ReqType rt) {
    ID id;
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
        if (m_requirements.getElementByIdx(k).id.isEqual(id)) {
            m_requirements.removeElementByIdx(k);
            return true;
        }
    }
    return false;
};

