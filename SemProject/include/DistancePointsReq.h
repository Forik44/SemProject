#pragma once 

#include "IReq.h"
#include "Dict.h"

class DistancePointsReq : public BasicReq
{
private:
    TreeDict<ID, Point>* m_storage;
public:
    DistancePointsReq(TreeDict<ID, Point>* storage, ID id1, ID id2, double distance) :
        m_storage(storage),
        dist(distance),
        BasicReq(id1, id2) {};
    virtual double getError();
    double dist;
};

double DistancePointsReq::getError()
{
    TreeDict<ID, Point>::iterator mark;
    mark = m_storage->begin();
    while ((*mark).key != m_id1)
        mark++;
    Point& p1 = (*mark).value;

    mark = m_storage->begin();
    while ((*mark).key != m_id2)
        mark++;
    Point& p2 = (*mark).value;

    return abs(dist - sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}
