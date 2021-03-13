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


//Проба пера
class ID{
private: //Проба пера
    static int m_counterID;
    int m_id;//Проба пера
public:
    ID()
    {
        m_id = -1;
    }
    ID(const ID& original)
    {
        m_id = original.m_id;
    }
    static ID generateID()
    {
        ID newid;
        newid.m_id = ID::m_counterID++;
        return newid;
    }
    bool operator ==(const ID& other)
    {
        return (other.m_id == this->m_id);//Проба пера
    }
    bool operator < (const ID& other)
    {
        return (other.m_id < this->m_id);
    }
};



struct ReqParallel
{
    double error()
    {
        Segment l1, l2;

        double A1 = l1.p1.x - l1.p2.x;
        double B1 = l1.p1.y - l1.p2.y;
        double length = sqrt(A1 * A1 + B1 * B1);
        A1 = A1 / length;
        B1 = B1 / length;

        double A2 = l2.p1.x - l2.p2.x;
        double B2 = l2.p1.y - l2.p2.y;
        length = sqrt(A2 * A2 + B2 * B2);
        A2 = A2 / length;
        B2 = B2 / length;

        return abs(abs(A1) - abs(A2) + abs(B1) - abs(B2));
    }
};

struct ReqOrtho
{
    double error()
    {
        Segment l1, l2;
        double A1 = l1.p1.x - l1.p2.x;
        double B1 = l1.p1.y - l1.p2.y;
        double A2 = l2.p1.x - l2.p2.x;
        double B2 = l2.p1.y - l2.p2.y;

        return abs(A1 * A2 + B1 * B2);
        
    }
};

struct ReqDist
{
    double error(double dist)
    {
        if (false) //2 points
        {
            Point p1, p2;
            return abs(dist - sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
        }
        else if (false) //point and line
        {
            Segment l;
            Point p;
            double A = l.p2.y - l.p1.y;
            double B = l.p1.x - l.p2.x;
            double C = l.p2.x * l.p1.y - l.p1.x * l.p2.y;
            return abs(dist - abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B));
        }
        else if (false) //2 lines 
        {
            Segment l1, l2;
            if (false) //ReqParallel.error() == 0
            {
                double A1 = l1.p2.y - l1.p1.y;
                double B1 = l1.p1.x - l1.p2.x;
                double C1 = l1.p2.x * l1.p1.y - l1.p1.x * l1.p2.y;

                return abs(dist - abs(A1 * l2.p1.x + B1 * l2.p1.y + C1) / sqrt(A1 * A1 + B1 * B1));
            }
        }
        
    };
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



