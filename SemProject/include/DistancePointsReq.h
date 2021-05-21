#pragma once 

#include "IReq.h"
#include <map>

class DistancePointsReq : public BasicReq
{
private:
    std::map<ID, Point>* m_storage;
public:
    DistancePointsReq(std::map<ID, Point>* storage, ID id1, ID id2, double distance) :
        m_storage(storage),
        dist(distance),
        BasicReq(id1, id2) {};
    virtual double getError();
    double dist;
};

double DistancePointsReq::getError()
{
    std::map<ID, Point>::const_iterator mark = m_storage->find(m_id1);
    if ( mark == m_storage->end() ) throw std::runtime_error("No point");
    const Point& p1 = (*mark).second;

    mark = m_storage->find(m_id2);
    if ( mark == m_storage->end() ) throw std::runtime_error("No point");
    const Point& p2 = (*mark).second;

    return abs(dist - sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}
