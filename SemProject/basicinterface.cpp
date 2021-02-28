#include "basicinterface.h"

BasicInterface::BasicInterface()
{

}
ID  BasicInterface::addObject(ObjType ot)
{
    ID id;
    switch (ot){
    case OT_POINT:
        m_points.add({id,Point()});
        break;
    case OT_SEGMENT:
        break;
    case OT_CIRCLE:
        ;
    }
    return id;

}
bool BasicInterface::removeObject(ID id ){
    for (size_t k = 0; k < m_points.getSize() ;++k){
        if (m_points.getElementByIdx(k).id.isEqual(id)){
            m_points.removeByIdx(k);
            return true;
        }
    }
    for (size_t k = 0; k < m_segments.getSize();++k) {
        if (m_segments.getElementByIdx(k).id.isEqual(id)) {
            m_segments.removeByIdx(k);
            return true;
        }
    }
    for (size_t k = 0; k < m_circles.getSize();++k) {
        if (m_circles.getElementByIdx(k).id.isEqual(id)) {
            m_circles.removeByIdx(k);
            return true;
        }
    }
    return false;
}

ID  BasicInterface::addRequirement(Array<ID>&, ReqType){

}

bool BasicInterface::removeRequirement(ID id){
    for (size_t k = 0; k < m_requirements.getSize();++k) {
        if (m_requirements.getElementByIdx(k).id.isEqual(id)) {
            m_requirements.removeByIdx(k);
            return true;
        }
    }
    return false;
}

