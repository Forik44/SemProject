#pragma once

#include "stdlib.h"
#include "Array.h"

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

static int counterID = 0;
//Проба пера
class ID{
private: //Проба пера
    int counterID = 0;
    int id;//Проба пера
public:
    ID()
    {
       
        id = counterID;//Проба пера
        counterID++;
    }
    ID(const ID& original)
    {
        id = counterID;
    }
    bool isEqual(const ID& id)
    {
        if (id.id == ID::id)//Проба пера
            return true;//Проба пера
        else//Проба пера
            return false;//Проба пера
    }
};



struct ReqParallel
{
    double error();
};

struct ReqOrtho
{
    double error();
};

struct ReqDist
{
    double error();
};

struct Requirement
{
    ReqType type;
    Array<ID> objs;
};


template <typename T>
class Identifiable
{
public:
    ID id;
    T obj;
};



