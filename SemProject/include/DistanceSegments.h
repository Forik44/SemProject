
#pragma once 

#include "IReq.h"
#include "Dict.h"

class DistanceSegmentsReq : public BasicReq
{
private:
    TreeDict<ID, Segment>* m_storage;
public:
    DistanceSegmentsReq(TreeDict<ID, Segment>* storage, ID id1, ID id2, double distance) :
        m_storage(storage),
        dist(distance),
        BasicReq(id1, id2) {};
    double getError();
    double dist;
};

double DistanceSegmentsReq::getError()
{
    TreeDict<ID, Segment>::iterator mark;
    mark = m_storage->begin();
    while ((*mark).key != m_id1)
        mark++;
    Segment& l1 = (*mark).value;

    mark = m_storage->begin();
    while ((*mark).key != m_id2)
        mark++;
    Segment& l2 = (*mark).value;


    double A1 = l1.p2.y - l1.p1.y;
    double B1 = l1.p1.x - l1.p2.x;
    double C1 = l1.p2.x * l1.p1.y - l1.p1.x * l1.p2.y;

    return abs(dist - abs(A1 * l2.p1.x + B1 * l2.p1.y + C1) / sqrt(A1 * A1 + B1 * B1));


}
