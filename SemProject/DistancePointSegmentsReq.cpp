#include "DistancePointSegmentReq.h"

double DistancePointSegmentReq::getError() {

    Point& p = (*m_storageP)[m_seg1];
    Segment& l = (*m_storageS)[m_seg2];
    double A = l.p2.y - l.p1.y;
    double B = l.p1.x - l.p2.x;
    double C = l.p2.x * l.p1.y - l.p1.x * l.p2.y;
    return abs(distance - abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B));
}