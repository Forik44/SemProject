#pragma once 

#include "IReq.h"
#include <map>

class DistancePointSegmentReq : public BasicReq
{
private:
    std::map<ID, Segment>* m_storage_segment;
    std::map<ID, Point>* m_storage_point;
public:
    DistancePointSegmentReq(std::map<ID, Point>* pointStorage, std::map<ID, Segment>* segmentStorage, ID pointID, ID segmentID, double distance) :
        m_storage_segment(segmentStorage),
        m_storage_point(pointStorage),
        dist(distance),
        BasicReq(pointID, segmentID) {};
    double getError();
    double dist;
};

double DistancePointSegmentReq::getError()
{
    std::map<ID, Point>::const_iterator mark1;
    mark1 = m_storage_point->find(m_id1);
    if ( mark1 == m_storage_point->end() ) throw std::runtime_error("No point");
    const Point& p = (*mark1).second;

    std::map<ID, Segment>::const_iterator mark2;
    mark2 = m_storage_segment->find(m_id2);
    if ( mark2 == m_storage_segment->end() ) throw std::runtime_error("No segment");


    const Segment& l = (*mark2).second;

    double A = l.p2.y - l.p1.y;
    double B = l.p1.x - l.p2.x;
    double C = l.p2.x * l.p1.y - l.p1.x * l.p2.y;

    return abs(dist - abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B));


}
