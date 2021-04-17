#ifndef PARALLELREQ_H
#define PARALLELREQ_H
#include "IReq.h"
#include "objects.h"
#include "Dict.h"

class ParallelReq: public IReq
{
public:
    ParallelReq(UniDict<ID, Segment>* storage,
                ID s1,
                ID s2):
        m_storage(storage),
        m_seg1(s1),
        m_seg2(s2){

    };
    double getError();
private:
    UniDict<ID, Segment> *m_storage;
    ID m_seg1, m_seg2;
};

class MultiParallelReq: public IReq
{
public:
    MultiParallelReq(UniDict<ID, Segment>* storage,
                const Array<ID>& ids ):
        m_storage(storage),
        m_ids(ids){

    };
    double getError();
private:
    UniDict<ID, Segment> *m_storage;
    Array<ID> m_ids;
};



#endif // PARALLELREQ_H
