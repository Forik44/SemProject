#include "DistanceSegmentsReq.h"

double DistanceSegmentsReq::getError() {

    Segment& l1 = (*m_storage)[m_seg1];
    Segment& l2 = (*m_storage)[m_seg2];
    double A1 = l1.p2.y - l1.p1.y;
    double B1 = l1.p1.x - l1.p2.x;
    double C1 = l1.p2.x * l1.p1.y - l1.p1.x * l1.p2.y;

        return abs(distance - abs(A1 * l2.p1.x + B1 * l2.p1.y + C1) / sqrt(A1 * A1 + B1 * B1));
}