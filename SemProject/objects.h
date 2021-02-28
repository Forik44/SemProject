#pragma once

#include "stdlib.h"
#include "Array.h"
#include "Array.cpp"

enum ObjType{
    OT_POINT,
    OT_SEGMENT,
    OT_CIRCLE
};
enum ReqType{
    RT_PARALLEL,
    RT_ORTHO,
    RT_COINCIDE,
    RT_GROUP,
    RT_DISTANCE
};


struct Point
{
    //Colors color;
    int x;
    int y;
};
struct Segment
{
    //Colors color;
    Point p1;
    Point p2;
};

struct Circle
{
    //Colors color;
    Point center;
    int r;
};


class ID{
public:
    ID()
    {
    }
    bool isEqual(const ID&)
    {
        return 1;
    }
   
};

struct Requirement{
    ReqType type;
    Array<ID> objs;
};


template <typename T>
class Identifiable{
public:
    ID id;
    T obj;
};

