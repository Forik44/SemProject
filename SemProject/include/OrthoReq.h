#pragma once 

#include "IReq.h"
#include "Dict.h"

class OrthoReq: public BasicReq
{
private:
    TreeDict<ID, Segment>* m_storage;
public:
    OrthoReq(TreeDict<ID, Segment>* storage, ID id1, ID id2) :
        m_storage(storage),
        BasicReq(id1, id2) {};
    virtual double getError();
};

double OrthoReq::getError()
{
    TreeDict<ID, Segment>::Marker mark;
    mark = m_storage->init();
    while ((*mark).key != m_id1)
        mark++;
    Segment& l1 = (*mark).value;

    mark = m_storage->init();
    while ((*mark).key != m_id2)
        mark++;
    Segment& l2 = (*mark).value;

    double A1 = l1.p1.x - l1.p2.x;
    double B1 = l1.p1.y - l1.p2.y;
    double A2 = l2.p1.x - l2.p2.x;
    double B2 = l2.p1.y - l2.p2.y;

    return abs(A1 * A2 + B1 * B2);
    
}
