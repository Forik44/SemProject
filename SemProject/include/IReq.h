#pragma once

#include "Array.h"
#include  "objects.h"
class IReq{
public:
    virtual double getError() = 0;
};

class BasicReq : public IReq
{
public:
    BasicReq(ID id1, ID id2) : m_id1(id1), m_id2(id2) {};
protected:
    ID m_id1, m_id2;
};


