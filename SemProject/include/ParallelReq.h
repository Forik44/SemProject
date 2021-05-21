#pragma once 

#include "IReq.h"
#include <map>
#include <stdexcept>

class ParallelReq : public BasicReq
{
private:
    std::map<ID, Segment>* m_storage;
public:
    ParallelReq(std::map<ID, Segment>* storage, ID id1, ID id2) :
        m_storage(storage),
        BasicReq(id1, id2) {};
    virtual double getError();
};

double ParallelReq::getError() {

    std::map<ID, Segment>::iterator mark;
    mark = m_storage->find(m_id1);
    if (mark == m_storage->end() ) throw std::runtime_error("No segment");

    Segment& l1 = (*mark).second;

    mark = m_storage->find(m_id2);
    if (mark == m_storage->end() ) throw std::runtime_error("No segment");

    Segment& l2 = (*mark).second;

    double length;

    double X1 = l1.p1.x - l1.p2.x;
    double Y1 = l1.p1.y - l1.p2.y;

    double X2 = l2.p1.x - l2.p2.x;
    double Y2 = l2.p1.y - l2.p2.y;

    return abs(X1 * Y2 - X2 * Y1);
}






