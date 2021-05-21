
#pragma once 

#include "IReq.h"
#include <map>

class DistanceSegmentsReq : public BasicReq
{
private:
    std::map<ID, Segment>* m_storage;
public:
    DistanceSegmentsReq(std::map<ID, Segment>* storage, ID id1, ID id2, double distance) :
        m_storage(storage),
        dist(distance),
        BasicReq(id1, id2) {};
    double getError();
    double dist;
};

double DistanceSegmentsReq::getError()
{
    std::map<ID, Segment>::const_iterator mark;
    mark = m_storage->find( m_id1);
    if ( mark == m_storage->end() ) throw std::runtime_error("No segment");

    const Segment& l1 = (*mark).second;

    mark = m_storage->find(m_id2);
    if ( mark == m_storage->end() ) throw std::runtime_error("No segment");

    const Segment& l2 = (*mark).second;


    double A1 = l1.p2.y - l1.p1.y;
    double B1 = l1.p1.x - l1.p2.x;
    double C1 = l1.p2.x * l1.p1.y - l1.p1.x * l1.p2.y;

    return abs(dist - abs(A1 * l2.p1.x + B1 * l2.p1.y + C1) / sqrt(A1 * A1 + B1 * B1));


}
