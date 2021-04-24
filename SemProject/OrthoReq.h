#pragma once 

#include "IReq.h"
#include "Dict.h"

class OrthoReq: public BasicReq
{
private:
    UniDict<ID, Segment>* m_storage;
public:
    OrthoReq(UniDict<ID, Segment>* storage, const Array<ID>& idArr) :
        m_storage(storage),
        BasicReq(idArr) {};
    virtual double getError();
};




