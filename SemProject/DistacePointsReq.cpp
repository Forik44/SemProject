#include "DistacePointsReq.h"

double DistancePointsReq::getError() {
	Point& p1 = (*m_storage)[m_seg1];
	Point& p2 = (*m_storage)[m_seg2];

	return abs(distance - sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

