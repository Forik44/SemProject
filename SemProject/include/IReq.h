#ifndef IREQ_H
#define IREQ_H
#include "Array.h"
#include  "objects.h"
class IReq{
public:
    virtual double getError() = 0;
    Array<ID> objectsofReq() const;
};

#endif // IREQ_H
