#pragma once
#include <iostream>
#include <ctime>
#include "basicinterface.h"
#include "ParallelReq.h"
#include "OrthoReq.h"

#include "DistancePointSegmentReq.h"
#include "DistancePointsReq.h"
#include "DistanceSegments.h"

BasicInterface::BasicInterface()
{};
/*template<typename ArrayElement> std::vector<ArrayElement>::Array(const std::vector<ArrayElement>& original)
{
	//Копирующий конструктор
};
template<typename ArrayElement> std::vector<ArrayElement>::~Array()
{
	if (m_points != nullptr)
		delete[] m_points;
	if (m_circles != nullptr)
		delete[] m_points;
	if (m_segments != nullptr)
		delete[] m_points;
	if (m_points != nullptr)
		delete[] m_points;
};*/
ID  BasicInterface::addObject(ObjType ot)
{
	ID id = ID::generateID();
	srand(time(NULL));
	switch (ot)
	{
	case OT_POINT:
		Point p;
		p.x = rand() % 500;
		p.y = rand() % 500;
        m_points[id] = p;
		break;
	case OT_SEGMENT:
		Segment s;
		s.p1.x = rand() % 500;
		s.p1.y = rand() % 500;
		s.p2.x = rand() % 500;
		s.p2.y = rand() % 500;
        m_segments[id] =  s;
		break;
	case OT_CIRCLE:
		Circle c;
		c.center.x = rand() % 500;
		c.center.y = rand() % 500;
		c.r = rand() % 500;
        m_circles[id] = c;
		break;
	}
	calcbox(id, ot);
	return id;
};


std::ostream& operator<<(std::ostream& ost, const Segment& s)
{
	ost << '(' << s.p1.x << ',' << s.p1.y << "),(" << s.p2.x << ',' << s.p2.y << ')';
	return ost;
}

Segment BasicInterface::calcbox(ID id, ObjType ot) {
	Segment s;
	switch (ot)
	{
	case OT_SEGMENT:
		s.p1.x = m_segments[id].p1.x;
		s.p1.y = m_segments[id].p1.y;
		s.p2.x = m_segments[id].p1.x;
		s.p2.y = m_segments[id].p1.y;
		if (m_segments[id].p2.x < s.p1.x) s.p1.x = m_segments[id].p2.x;
		if (m_segments[id].p2.x > s.p2.x) s.p2.x = m_segments[id].p2.x;
		if (m_segments[id].p2.y < s.p1.y) s.p1.y = m_segments[id].p2.y;
		if (m_segments[id].p2.y > s.p2.y) s.p2.y = m_segments[id].p2.y;
	break;
	case OT_POINT:
		s.p1.x = m_points[id].x - 0.5;
		s.p1.y = m_points[id].y - 0.5;
		s.p2.x = m_points[id].x + 0.5;
		s.p2.y = m_points[id].y + 0.5;
		break;
	case OT_CIRCLE :
		s.p1.x = m_circles[id].center.x-m_circles[id].r;
		s.p1.y = m_circles[id].center.y-m_circles[id].r;
		s.p2.x = m_circles[id].center.x+m_circles[id].r;
		s.p2.y = m_circles[id].center.y+m_circles[id].r;
		std::cout << "CIRCLE";
	break;
	}
	std::cout << s << std::endl;
	//system("pause");
	return s;
}







bool BasicInterface::removeObjectByID(ID id)
{
	ObjType ot = identifyObjTypeByID(id);

	switch (ot)
	{
	case OT_CIRCLE:
        m_circles.erase(id);
		break;
	case OT_POINT:
        m_points.erase(id);
		break;
	case OT_SEGMENT:
        m_segments.erase(id);
		break;
	case OT_ERROR:
		return false;
	}

	int i = 0;
    std::vector<ID> arrID;
	/*
    for (std::map<ID, Requirement>::iterator m1 = m_requirements.begin(); m1 != m_requirements.end(); m1++, i++)
	{
        for (std::vector<ID>::iterator m2 = (*m1).val.objs.begin(); m2 != (*m1).val.objs.end(); m2++)
		{
			if ((*m2) == id)
			{
                arrID.add((*m1).first);
				break;
			}
		}
	};
	*/
    for (int i = 0; i < arrID.size(); i++)
	{
        m_requirements.erase(arrID[i]);
	}

	return false;
};
bool BasicInterface::removeRequirementByID(ID id)
{
	///////////////////////////////////////////////////////////Удалить выделенную под Req память/////////////////////////////////////////////////////////
    return m_requirements.erase(id);
};
std::vector<ID>& BasicInterface::addRequirement(const std::vector<ID>& idArr, ReqType rt, double dist)
{
	ID id;
    std::vector<ID> reqIds;
	bool segmentWasFound = 0, pointWasFound = 0, circleWasFound = 0;

    for (int i = 0; i < idArr.size(); i++)
	{
		ObjType ot = identifyObjTypeByID(idArr[i]);
		switch (ot)
		{
		case OT_POINT:
			pointWasFound = true;
			break;
		case OT_SEGMENT:
			segmentWasFound = true;
			break;
		case OT_CIRCLE:
			circleWasFound = true;
			break;
		default:
			throw;
			break;
		}
	}

	switch (rt)
	{
	case RT_PARALLEL:
	{
		if (pointWasFound || circleWasFound)
		{
			std::cout << "RT_PARALLEL: invalid parameter\n";
			throw;
		}

        for (int i = 0; i < idArr.size() - 1; i++)
		{
			ParallelReq* req = new ParallelReq(&m_segments, idArr[i], idArr[i + 1]);
			id = ID::generateID();
            reqIds.push_back(id);
            m_requirements[id] = req;
		}

		break;
	}
	case RT_ORTHO:
	{
		if (pointWasFound || circleWasFound)
		{
			std::cout << "RT_ORTHO: invalid parameter\n";
			throw;
		}

        for (int i = 0; i < idArr.size() - 1; i++)
		{
			OrthoReq* req = new OrthoReq(&m_segments, idArr[i], idArr[i + 1]);
			id = ID::generateID();
            reqIds.push_back(id);
            m_requirements[id] = req;
		}

		break;
	}
	case RT_COINCIDE:
		std::cout << "RT_COINCIDE: hasn't added yet\n";
		throw;
		break;
	case RT_GROUP:
		std::cout << "RT_GROUP: hasn't added yet\n";
		throw;
		break;
	case RT_DISTANCE:
	{
		if (circleWasFound)
		{
			std::cout << "RT_DISTANCE: invalid parameter\n";
			throw;
		}

		if (!segmentWasFound)
		{
            for (int i = 0; i < idArr.size() - 1; i++)
			{
				DistancePointsReq* req = new DistancePointsReq(&m_points, idArr[i], idArr[i + 1], dist);
				id = ID::generateID();
                reqIds.push_back(id);
                m_requirements[id] = req;
			}
		}
		else if (!pointWasFound)
		{
			//TODO Проверить, если два отрезка, то они должны быть параллельны
            for (int i = 0; i < idArr.size() - 1; i++)
			{
				DistanceSegmentsReq* req = new DistanceSegmentsReq(&m_segments, idArr[i], idArr[i + 1], dist);
				id = ID::generateID();
                reqIds.push_back(id);
                m_requirements[id] = req;
			}
		}
		else
		{

            for (int i = 0; i < idArr.size(); i++)
			{
				if (identifyObjTypeByID(idArr[i]) == OT_POINT)
                    for (int k = 0; k < idArr.size(); k++)
						if (identifyObjTypeByID(idArr[k]) == OT_SEGMENT)
						{

							DistancePointSegmentReq* req = new DistancePointSegmentReq(&m_points, &m_segments, idArr[i], idArr[k], dist);
							id = ID::generateID();
                            reqIds.push_back(id);
                            m_requirements[id]  = req;
						}

			}

		}



	}
	}

	return reqIds;
};
std::map<ParamType, double> BasicInterface::queryObjProperties(ID id)
{
	switch (identifyObjTypeByID(id))
	{
	case OT_CIRCLE:
	{
        //std::map<ID, Circle>::iterator cm = m_circles.begin();
        std::map<ID, Circle>::iterator cm = m_circles.begin();
        while ((*cm).first != id)
			cm++;

        std::map<ParamType, double> arr;
        arr[PT_CIRCLE] = 4;
        arr[PT_CX] = (*cm).second.center.x;
        arr[PT_CY] = (*cm).second.center.y;
        arr[PT_R] = (*cm).second.r;

		return arr;
		break;
	}
	case OT_POINT:
	{
        std::map<ID, Point>::iterator  pm = m_points.begin();

        //std::map<ID, Point>::iterator pm = m_points.begin();
        while ((*pm).first!= id)
			pm++;

        std::map<ParamType, double> arr;
        arr[PT_POINT] = 3;
        arr[PT_PX] = (*pm).second.x;
        arr[PT_PY] = (*pm).second.y;

		return arr;
		break;

	}
	case OT_SEGMENT:
	{
        //std::map<ID, Segment>::iterator sm = m_segments.begin();
        std::map<ID, Segment>::iterator sm = m_segments.begin();

        while ((*sm).first != id)
			sm++;

        std::map<ParamType, double> arr;
        arr[PT_SEGMENT] = 5;
        arr[PT_P1X] = (*sm).second.p1.x;
        arr[PT_P1Y] = (*sm).second.p1.y;
        arr[PT_P2X] = (*sm).second.p2.x;
        arr[PT_P2Y] = (*sm).second.p2.y;

		return arr;
		break;
	}
	default:
	{
        std::map<ParamType, double> arr;
        arr[PT_ERROR] =  -1;
		return arr;
	}
	}
}
ObjType BasicInterface::identifyObjTypeByID(ID id)
{
    std::map<ID, Point>::iterator pm = m_points.begin();
    while (pm != m_points.end())
	{
        if ((*pm).first == id)
			return OT_POINT;
		pm++;
	};
    std::map<ID, Circle>::iterator cm = m_circles.begin();
    while (cm != m_circles.end())
	{
        if ((*cm).first == id)
			return OT_CIRCLE;
		cm++;
	}
    std::map<ID, Segment>::iterator sm = m_segments.begin();
    while (sm != m_segments.end())
	{
        if ((*sm).first == id)
			return OT_SEGMENT;
		sm++;
	}
	return OT_ERROR;
}
std::vector<double> BasicInterface::getX()
{
    std::vector<double> res;

    std::map<ID, Point>::iterator pointMarker = m_points.begin();
    while (pointMarker != m_points.end())
	{
        res.push_back((*pointMarker).second.x);
        res.push_back((*pointMarker).second.y);
		pointMarker++;
	}

    std::map<ID, Segment>::iterator segmentMarker = m_segments.begin();
    while (segmentMarker != m_segments.end())
	{
        res.push_back((*segmentMarker).second.p1.x);
        res.push_back((*segmentMarker).second.p1.y);
        res.push_back((*segmentMarker).second.p2.x);
        res.push_back((*segmentMarker).second.p2.y);
		segmentMarker++;
	}

    std::map<ID, Circle>::iterator circleMarker = m_circles.begin();
    while (circleMarker != m_circles.end())
	{
        res.push_back((*circleMarker).second.center.x);
        res.push_back((*circleMarker).second.center.y);
        res.push_back((*circleMarker).second.r);
		circleMarker++;
	}

	return res;
}
void BasicInterface::setX(const std::vector<double>& X)
{
	size_t i = 0;
    std::map<ID, Point>::iterator pointMarker = m_points.begin();

    while (pointMarker != m_points.end())
	{
        (*pointMarker).second.x = X[i];
		i++;
        (*pointMarker).second.y = X[i];
		i++;
		pointMarker++;
	}

    std::map<ID, Segment>::iterator segmentMarker = m_segments.begin();
    while (segmentMarker != m_segments.end())
	{
        (*segmentMarker).second.p1.x = X[i];
		i++;
        (*segmentMarker).second.p1.y = X[i];
		i++;
        (*segmentMarker).second.p2.x = X[i];
		i++;
        (*segmentMarker).second.p2.y = X[i];
		i++;
		segmentMarker++;
	}

    std::map<ID, Circle>::iterator circleMarker = m_circles.begin();
    while (circleMarker != m_circles.end())
	{
        (*circleMarker).second.center.x = X[i];
		i++;
        (*circleMarker).second.center.y = X[i];
		i++;
        (*circleMarker).second.r = X[i];
		i++;
		segmentMarker++;
	}
}
double BasicInterface::particularErrValue(ID id1, ID id2, ReqType rt, double distance)
{
	ObjType ot1, ot2;
	ot1 = identifyObjTypeByID(id1);
	ot2 = identifyObjTypeByID(id2);

	if (rt == RT_PARALLEL)
	{
		if ((ot1 != OT_SEGMENT) || (ot2 != OT_SEGMENT))
			return -1;

        std::map<ID, Segment>::iterator mark;
        mark = m_segments.begin();
        while ((*mark).first != id1)
			mark++;
        Segment& l1 = (*mark).second;

        mark = m_segments.begin();
        while ((*mark).first != id2)
			mark++;
        Segment& l2 = (*mark).second;


		double length;

		double X1 = l1.p1.x - l1.p2.x;
		double Y1 = l1.p1.y - l1.p2.y;

		double X2 = l2.p1.x - l2.p2.x;
		double Y2 = l2.p1.y - l2.p2.y;

		return abs(X1 * Y2 - X2 * Y1);
	}
	else if (rt == RT_ORTHO)
	{
		if ((ot1 != OT_SEGMENT) || (ot2 != OT_SEGMENT))
			return -1;

        std::map<ID, Segment>::iterator mark;
        mark = m_segments.begin();
        while ((*mark).first != id1)
			mark++;
        Segment& l1 = (*mark).second;

        mark = m_segments.begin();
        while ((*mark).first != id2)
			mark++;
        Segment& l2 = (*mark).second;

		double A1 = l1.p1.x - l1.p2.x;
		double B1 = l1.p1.y - l1.p2.y;
		double A2 = l2.p1.x - l2.p2.x;
		double B2 = l2.p1.y - l2.p2.y;

		return abs(A1 * A2 + B1 * B2);
	}
	else if (rt == RT_DISTANCE)
	{
		if ((ot1 == OT_POINT) && (ot2 == OT_POINT)) //2 points
		{
            std::map<ID, Point>::iterator mark;
            mark = m_points.begin();
            while ((*mark).first != id1)
				mark++;
            Point& p1 = (*mark).second;

            mark = m_points.begin();
            while ((*mark).first != id2)
				mark++;
            Point& p2 = (*mark).second;

			return abs(distance - sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
		}
		else if ((ot1 == OT_POINT) && (ot2 == OT_SEGMENT)) //point and line
		{
            std::map<ID, Point>::iterator mark1;
            mark1 = m_points.begin();
            while ((*mark1).first != id1)
				mark1++;
            Point& p = (*mark1).second;

            std::map<ID, Segment>::iterator mark2;
            mark2 = m_segments.begin();
            while ((*mark2).first != id2)
				mark2++;
            Segment& l = (*mark2).second;

			double A = l.p2.y - l.p1.y;
			double B = l.p1.x - l.p2.x;
			double C = l.p2.x * l.p1.y - l.p1.x * l.p2.y;

			return abs(distance - abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B));
		}
		else if ((ot2 == OT_POINT) && (ot1 == OT_SEGMENT)) //point and line
		{
            std::map<ID, Point>::iterator mark1;
            mark1 = m_points.begin();
            while ((*mark1).first != id2)
				mark1++;
            Point& p = (*mark1).second;

            std::map<ID, Segment>::iterator mark2;
            mark2 = m_segments.begin();
            while ((*mark2).first != id1)
				mark2++;
            Segment& l = (*mark2).second;


			double A = l.p2.y - l.p1.y;
			double B = l.p1.x - l.p2.x;
			double C = l.p2.x * l.p1.y - l.p1.x * l.p2.y;
			return abs(distance - abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B));
		}
		else if ((ot2 == OT_SEGMENT) && (ot1 == OT_SEGMENT)) //2 lines 
		{
            std::map<ID, Segment>::iterator mark;
            mark = m_segments.begin();
            while ((*mark).first != id1)
				mark++;
            Segment& l1 = (*mark).second;

            mark = m_segments.begin();
            while ((*mark).first != id2)
				mark++;
            Segment& l2 = (*mark).second;

			if (particularErrValue(id1, id2, RT_PARALLEL) <= 0.01)
			{
				double A1 = l1.p2.y - l1.p1.y;
				double B1 = l1.p1.x - l1.p2.x;
				double C1 = l1.p2.x * l1.p1.y - l1.p1.x * l1.p2.y;

				return abs(distance - abs(A1 * l2.p1.x + B1 * l2.p1.y + C1) / sqrt(A1 * A1 + B1 * B1));
			}
			else
			{
				std::cout << "ERROR: Not parallel\n";
				return -1;
			}

		}
	}
	std::cout << "ERROR: ReqValue\n";
	return -1;
};
double  BasicInterface::partDerivative(int varNumber, ID id1, ID id2, ReqType rt, double distance)
{
    std::vector<double> arr = getX();

    if (arr.size() <= varNumber)
		return 0;

	double delta = 1e-10;
	double var = arr[varNumber];

	double req1 = particularErrValue(id1, id2, rt, distance);
	if (req1 == -1)
	{
		std::cout << "req1 error\n";
		return 0;
	}

	arr[varNumber] = var + delta;
	setX(arr);

	double req2 = particularErrValue(id1, id2, rt, distance);
	if (req2 == -1)
	{
		std::cout << "req2 error\n";
		return 0;
	}

	arr[varNumber] = var;
	setX(arr);

	return (req2 - req1) / delta;
}
void BasicInterface::solveParticularReq(ID id1, ID id2, ReqType rt, double distance)
{
    std::vector<double> arr = getX();

	double secondReqValue, firstReqValue = particularErrValue(id1, id2, rt, distance);

	std::cout << "Req value before: " << firstReqValue << std::endl;

	double lambda = 0.1;
	while (firstReqValue > 0.0001)
	{
        std::vector<double> devArr, newArr;

		firstReqValue = particularErrValue(id1, id2, rt, distance);

		int i = 0;
        for (std::vector<double>::iterator m = arr.begin(); m != arr.end(); m++, i++)
		{
            devArr.push_back(partDerivative(i, id1, id2, rt, distance));   //Составляем вектор производных
		};

		i = 0;
        for (std::vector<double>::iterator m = arr.begin(); m != arr.end(); m++, i++)
		{
            newArr.push_back(arr[i] - lambda * devArr[i]);   //Составляем новый вектор координат
		};

		setX(newArr);

		secondReqValue = particularErrValue(id1, id2, rt, distance);

		if (secondReqValue > firstReqValue)   //Если ситуация не улучшилась
		{
			setX(arr);
			lambda = lambda / 10;
		}
		else
		{
			firstReqValue = secondReqValue;
			i = 0;
            for (std::vector<double>::iterator m = arr.begin(); m != arr.end(); m++, i++)
			{
				arr[i] = newArr[i];
			};
		}
	}

	std::cout << "Req value after: " << firstReqValue << std::endl;
}
double BasicInterface::complexErrValue()
{
	double complexError = 0;

    for (std::map<ID, IReq*>::iterator reqMark = m_requirements.begin(); reqMark != m_requirements.end(); reqMark++)
        complexError += (*reqMark).second->getError();

	return complexError;
};
bool BasicInterface::solveComplexReq()
{
    std::vector<double> arr = getX();

	double secondReqValue, firstReqValue = complexErrValue();

	/*std::cout << "Req value before: " << firstReqValue << std::endl;*/

	double lambda = 0.1;
	while (firstReqValue > 1e-2)
	{
        std::vector<double> devArr, newArr;

		firstReqValue = complexErrValue();

		int i = 0;
        for (std::vector<double>::iterator m = arr.begin(); m != arr.end(); m++, i++)
		{
            devArr.push_back(complexPartDerivative(i));   //Составляем вектор производных
		};

		i = 0;
        for (std::vector<double>::iterator m = arr.begin(); m != arr.end(); m++, i++)
		{
            newArr.push_back(arr[i] - lambda * devArr[i]);   //Составляем новый вектор координат
		};

		setX(newArr);

		secondReqValue = complexErrValue();
		/*std::cout << secondReqValue << " " << firstReqValue << "\n";*/
		if (secondReqValue > firstReqValue)   //Если ситуация не улучшилась
		{
			setX(arr);
			lambda = lambda / 2;
		}
		else
		{
			firstReqValue = secondReqValue;
			i = 0;
            for (std::vector<double>::iterator m = arr.begin(); m != arr.end(); m++, i++)
			{
				arr[i] = newArr[i];
			};
		}
	}

	/*  std::cout << "Req value after: " << firstReqValue << std::endl;*/
	return true;
}
double  BasicInterface::complexPartDerivative(int varNumber)
{
    std::vector<double> arr = getX();

    if (arr.size() <= varNumber)
		return 0;

	double delta = 1e-5;
	double var = arr[varNumber];

	double req1 = complexErrValue();
	if (req1 == -1)
	{
		std::cout << "ERROR: complexPartDerivative(req1)\n";
		return 0;
	}

	arr[varNumber] = var + delta;
	setX(arr);

	double req2 = complexErrValue();
	if (req2 == -1)
	{
		std::cout << "ERROR: complexPartDerivative(req2)\n";
		return 0;
	}

	arr[varNumber] = var;
	setX(arr);

	return (req2 - req1) / delta;
}
std::vector<ID> BasicInterface::ReceiveIdObjects()
{
    std::vector<ID> IDs;
    for (std::map<ID, Point>::iterator mark = m_points.begin();mark != m_points.end(); mark++)
	{
        IDs.push_back((*mark).first);
	}
    for (std::map<ID, Segment>::iterator mark = m_segments.begin();mark != m_segments.end(); mark++)
	{
        IDs.push_back((*mark).first);
	}
    for (std::map<ID, Circle>::iterator mark = m_circles.begin();mark != m_circles.end(); mark++)
	{
        IDs.push_back((*mark).first);
	}
	return IDs;
}
