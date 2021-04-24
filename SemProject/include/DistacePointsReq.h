#ifndef PARALLELREQ_H
#define PARALLELREQ_H
#include "IReq.h"
#include "objects.h"
#include "Dict.h"

class DistancePointsReq : public IReq
{
public:
    DistancePointsReq(UniDict<ID, Point>* storage,
        ID s1,
        ID s2,
        size_t dist) :
        m_storage(storage),
        m_seg1(s1),
        m_seg2(s2),
        distance(dist) {

    };
    double getError();
private:
    UniDict<ID, Point>* m_storage;
    ID m_seg1, m_seg2;
    size_t distance;
};





#endif // PARALLELREQ_H


