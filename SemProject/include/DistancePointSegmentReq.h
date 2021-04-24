#pragma once 

#include "IReq.h"
#include "Dict.h"

class DistancePointSegmentReq : public BasicReq
{
private:
    UniDict<ID, Segment>* m_storage_segment;
    UniDict<ID, Point>* m_storage_point;
public:
    DistancePointSegmentReq(UniDict<ID, Point>* pointStorage, UniDict<ID, Segment>* segmentStorage, ID pointID, ID segmentID, double distance) :
        m_storage_segment(segmentStorage),
        m_storage_point(pointStorage),
        dist(distance),
        BasicReq(pointID, segmentID) {};
    double getError();
    double dist;
};

double DistancePointSegmentReq::getError()
{
    UniDict<ID, Point>::Marker mark1;
    mark1 = m_storage_point->init();
    while ((*mark1).key != m_id1)
        mark1++;
    Point& p = (*mark1).val;

    UniDict<ID, Segment>::Marker mark2;
    mark2 = m_storage_segment->init();
    while ((*mark2).key != m_id2)
        mark2++;
    Segment& l = (*mark2).val;

    double A = l.p2.y - l.p1.y;
    double B = l.p1.x - l.p2.x;
    double C = l.p2.x * l.p1.y - l.p1.x * l.p2.y;

    return abs(dist - abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B));


}
