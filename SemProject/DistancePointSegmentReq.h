#ifndef PARALLELREQ_H
#define PARALLELREQ_H
#include "IReq.h"
#include "objects.h"
#include "Dict.h"
class DistancePointSegmentReq : public IReq
{
public:
    DistancePointSegmentReq(UniDict<ID, Point>* storageP,
        UniDict<ID, Segment>* storageS,
        ID s1,
        ID s2,
        size_t dist) :
        m_storageP(storageP),
        m_storageS(storageS),
        m_seg1(s1),
        m_seg2(s2),
        distance(dist) {

    };
        double getError();
private:
    UniDict<ID, Segment>* m_storageS;
    UniDict<ID, Point>* m_storageP;
    ID m_seg1, m_seg2;
    size_t distance;
};





#endif // PARALLELREQ_H


