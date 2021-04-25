#pragma once
#include <iostream>
#include "basicinterface.h"
#include "ParallelReq.h"
#include "OrthoReq.h"

#include "DistancePointSegmentReq.h"
#include "DistancePointsReq.h"
#include "DistanceSegments.h"

BasicInterface::BasicInterface()
{};
ID  BasicInterface::addObject(ObjType ot)
{
	ID id = ID::generateID();
	switch (ot)
	{
	case OT_POINT:
		Point p;
		p.x = rand() % 100;
		p.y = rand() % 100;
		m_points.add(id, p);
		break;
	case OT_SEGMENT:
		Segment s;
		s.p1.x = rand() % 100;
		s.p1.y = rand() % 100;
		s.p2.x = rand() % 100;
		s.p2.y = rand() % 100;
		m_segments.add(id, s);
		break;
	case OT_CIRCLE:
		Circle c;
		c.center.x = rand() % 100;
		c.center.y = rand() % 100;
		c.r = rand() % 100;
		m_circles.add(id, c);
		break;
	}
	return id;
};
bool BasicInterface::removeObjectByID(ID id)
{
	ObjType ot = identifyObjTypeByID(id);

	switch (ot)
	{
	case OT_CIRCLE:
		m_circles.removeElementByKey(id);
		break;
	case OT_POINT:
		m_points.removeElementByKey(id);
		break;
	case OT_SEGMENT:
		m_segments.removeElementByKey(id);
		break;
	case OT_ERROR:
		return false;
	}

	int i = 0;
	Array<ID> arrID;
	/*
	for (TreeDict<ID, Requirement>::Marker m1 = m_requirements.init(); m1 != m_requirements.afterEnd(); m1++, i++)
	{
		for (Array<ID>::Marker m2 = (*m1).val.objs.init(); m2 != (*m1).val.objs.afterEnd(); m2++)
		{
			if ((*m2) == id)
			{
				arrID.add((*m1).key);
				break;
			}
		}
	};
	*/
	for (int i = 0; i < arrID.getSize(); i++)
	{
		m_requirements.removeElementByKey(arrID[i]);
	}

	return false;
};
bool BasicInterface::removeRequirementByID(ID id)
{
	///////////////////////////////////////////////////////////������� ���������� ��� Req ������/////////////////////////////////////////////////////////
	return m_requirements.removeElementByKey(id);
};
Array<ID>& BasicInterface::addRequirement(const Array<ID>& idArr, ReqType rt, double dist)
{
	ID id;
	Array<ID> reqIds;
	bool segmentWasFound = 0, pointWasFound = 0, circleWasFound = 0;

	for (int i = 0; i < idArr.getSize(); i++)
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

		for (int i = 0; i < idArr.getSize() - 1; i++)
		{
			ParallelReq* req = new ParallelReq(&m_segments, idArr[i], idArr[i + 1]);
			id = ID::generateID();
			reqIds.add(id);
			m_requirements.add(id, req);
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

		for (int i = 0; i < idArr.getSize() - 1; i++)
		{
			OrthoReq* req = new OrthoReq(&m_segments, idArr[i], idArr[i + 1]);
			id = ID::generateID();
			reqIds.add(id);
			m_requirements.add(id, req);
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
			for (int i = 0; i < idArr.getSize() - 1; i++)
			{
				DistancePointsReq* req = new DistancePointsReq(&m_points, idArr[i], idArr[i + 1], dist);
				id = ID::generateID();
				reqIds.add(id);
				m_requirements.add(id, req);
			}
		}
		else if (!pointWasFound)
		{
			//TODO ���������, ���� ��� �������, �� ��� ������ ���� �����������
			for (int i = 0; i < idArr.getSize() - 1; i++)
			{
				DistanceSegmentsReq* req = new DistanceSegmentsReq(&m_segments, idArr[i], idArr[i + 1], dist);
				id = ID::generateID();
				reqIds.add(id);
				m_requirements.add(id, req);
			}
		}
		else
		{

			for (int i = 0; i < idArr.getSize(); i++)
			{
				if (identifyObjTypeByID(idArr[i]) == OT_POINT)
					for (int k = 0; k < idArr.getSize(); k++)
						if (identifyObjTypeByID(idArr[k]) == OT_SEGMENT)
						{

							DistancePointSegmentReq* req = new DistancePointSegmentReq(&m_points, &m_segments, idArr[i], idArr[k], dist);
							id = ID::generateID();
							reqIds.add(id);
							m_requirements.add(id, req);
						}

			}

		}



	}
	}

	return reqIds;
};
TreeDict<ParamType, double> BasicInterface::queryObjProperties(ID id)
{
	switch (identifyObjTypeByID(id))
	{
	case OT_CIRCLE:
	{
		TreeDict<ID, Circle>::Marker cm = m_circles.init();
		while ((*cm).key != id)
			cm++;

		TreeDict<ParamType, double> arr;
		arr.add(PT_CIRCLE, 4);
		arr.add(PT_CX, (*cm).value.center.x);
		arr.add(PT_CY, (*cm).value.center.y);
		arr.add(PT_R, (*cm).value.r);

		return arr;
		break;
	}
	case OT_POINT:
	{
		TreeDict<ID, Point>::Marker pm = m_points.init();
		while ((*pm).key != id)
			pm++;

		TreeDict<ParamType, double> arr;
		arr.add(PT_POINT, 3);
		arr.add(PT_PX, (*pm).value.x);
		arr.add(PT_PY, (*pm).value.y);

		return arr;
		break;

	}
	case OT_SEGMENT:
	{
		TreeDict<ID, Segment>::Marker sm = m_segments.init();
		while ((*sm).key != id)
			sm++;

		TreeDict<ParamType, double> arr;
		arr.add(PT_SEGMENT, 5);
		arr.add(PT_P1X, (*sm).value.p1.x);
		arr.add(PT_P1Y, (*sm).value.p1.y);
		arr.add(PT_P2X, (*sm).value.p2.x);
		arr.add(PT_P2Y, (*sm).value.p2.y);

		return arr;
		break;
	}
	default:
	{
		TreeDict<ParamType, double> arr;
		arr.add(PT_ERROR, -1);
		return arr;
	}
	}
}
ObjType BasicInterface::identifyObjTypeByID(ID id)
{
	TreeDict<ID, Point>::Marker pm = m_points.init();
	while (pm != m_points.afterEnd())
	{
		if ((*pm).key == id)
			return OT_POINT;
		pm++;
	};
	TreeDict<ID, Circle>::Marker cm = m_circles.init();
	while (cm != m_circles.afterEnd())
	{
		if ((*cm).key == id)
			return OT_CIRCLE;
		cm++;
	}
	TreeDict<ID, Segment>::Marker sm = m_segments.init();
	while (sm != m_segments.afterEnd())
	{
		if ((*sm).key == id)
			return OT_SEGMENT;
		sm++;
	}
	return OT_ERROR;
}
Array<double> BasicInterface::getX()
{
	Array<double> res;

	TreeDict<ID, Point>::Marker pointMarker = m_points.init();
	while (pointMarker != m_points.afterEnd())
	{
		res.add((*pointMarker).value.x);
		res.add((*pointMarker).value.y);
		pointMarker++;
	}

	TreeDict<ID, Segment>::Marker segmentMarker = m_segments.init();
	while (segmentMarker != m_segments.afterEnd())
	{
		res.add((*segmentMarker).value.p1.x);
		res.add((*segmentMarker).value.p1.y);
		res.add((*segmentMarker).value.p2.x);
		res.add((*segmentMarker).value.p2.y);
		segmentMarker++;
	}

	TreeDict<ID, Circle>::Marker circleMarker = m_circles.init();
	while (circleMarker != m_circles.afterEnd())
	{
		res.add((*circleMarker).value.center.x);
		res.add((*circleMarker).value.center.y);
		res.add((*circleMarker).value.r);
		circleMarker++;
	}

	return res;
}
void BasicInterface::setX(const Array<double>& X)
{
	size_t i = 0;
	TreeDict<ID, Point>::Marker pointMarker = m_points.init();

	while (pointMarker != m_points.afterEnd())
	{
		(*pointMarker).value.x = X[i];
		i++;
		(*pointMarker).value.y = X[i];
		i++;
		pointMarker++;
	}

	TreeDict<ID, Segment>::Marker segmentMarker = m_segments.init();
	while (segmentMarker != m_segments.afterEnd())
	{
		(*segmentMarker).value.p1.x = X[i];
		i++;
		(*segmentMarker).value.p1.y = X[i];
		i++;
		(*segmentMarker).value.p2.x = X[i];
		i++;
		(*segmentMarker).value.p2.y = X[i];
		i++;
		segmentMarker++;
	}

	TreeDict<ID, Circle>::Marker circleMarker = m_circles.init();
	while (circleMarker != m_circles.afterEnd())
	{
		(*circleMarker).value.center.x = X[i];
		i++;
		(*circleMarker).value.center.y = X[i];
		i++;
		(*circleMarker).value.r = X[i];
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

		TreeDict<ID, Segment>::Marker mark;
		mark = m_segments.init();
		while ((*mark).key != id1)
			mark++;
		Segment& l1 = (*mark).value;

		mark = m_segments.init();
		while ((*mark).key != id2)
			mark++;
		Segment& l2 = (*mark).value;


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

		TreeDict<ID, Segment>::Marker mark;
		mark = m_segments.init();
		while ((*mark).key != id1)
			mark++;
		Segment& l1 = (*mark).value;

		mark = m_segments.init();
		while ((*mark).key != id2)
			mark++;
		Segment& l2 = (*mark).value;

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
			TreeDict<ID, Point>::Marker mark;
			mark = m_points.init();
			while ((*mark).key != id1)
				mark++;
			Point& p1 = (*mark).value;

			mark = m_points.init();
			while ((*mark).key != id2)
				mark++;
			Point& p2 = (*mark).value;

			return abs(distance - sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
		}
		else if ((ot1 == OT_POINT) && (ot2 == OT_SEGMENT)) //point and line
		{
			TreeDict<ID, Point>::Marker mark1;
			mark1 = m_points.init();
			while ((*mark1).key != id1)
				mark1++;
			Point& p = (*mark1).value;

			TreeDict<ID, Segment>::Marker mark2;
			mark2 = m_segments.init();
			while ((*mark2).key != id2)
				mark2++;
			Segment& l = (*mark2).value;

			double A = l.p2.y - l.p1.y;
			double B = l.p1.x - l.p2.x;
			double C = l.p2.x * l.p1.y - l.p1.x * l.p2.y;

			return abs(distance - abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B));
		}
		else if ((ot2 == OT_POINT) && (ot1 == OT_SEGMENT)) //point and line
		{
			TreeDict<ID, Point>::Marker mark1;
			mark1 = m_points.init();
			while ((*mark1).key != id2)
				mark1++;
			Point& p = (*mark1).value;

			TreeDict<ID, Segment>::Marker mark2;
			mark2 = m_segments.init();
			while ((*mark2).key != id1)
				mark2++;
			Segment& l = (*mark2).value;


			double A = l.p2.y - l.p1.y;
			double B = l.p1.x - l.p2.x;
			double C = l.p2.x * l.p1.y - l.p1.x * l.p2.y;
			return abs(distance - abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B));
		}
		else if ((ot2 == OT_SEGMENT) && (ot1 == OT_SEGMENT)) //2 lines 
		{
			TreeDict<ID, Segment>::Marker mark;
			mark = m_segments.init();
			while ((*mark).key != id1)
				mark++;
			Segment& l1 = (*mark).value;

			mark = m_segments.init();
			while ((*mark).key != id2)
				mark++;
			Segment& l2 = (*mark).value;

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
	Array<double> arr = getX();

	if (arr.getSize() <= varNumber)
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
	Array<double> arr = getX();

	double secondReqValue, firstReqValue = particularErrValue(id1, id2, rt, distance);

	std::cout << "Req value before: " << firstReqValue << std::endl;

	double lambda = 0.1;
	while (firstReqValue > 0.0001)
	{
		Array<double> devArr, newArr;

		firstReqValue = particularErrValue(id1, id2, rt, distance);

		int i = 0;
		for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
		{
			devArr.add(partDerivative(i, id1, id2, rt, distance));   //���������� ������ �����������
		};

		i = 0;
		for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
		{
			newArr.add(arr[i] - lambda * devArr[i]);   //���������� ����� ������ ���������
		};

		setX(newArr);

		secondReqValue = particularErrValue(id1, id2, rt, distance);

		if (secondReqValue > firstReqValue)   //���� �������� �� ����������
		{
			setX(arr);
			lambda = lambda / 10;
		}
		else
		{
			firstReqValue = secondReqValue;
			i = 0;
			for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
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

	for (TreeDict<ID, IReq*>::Marker reqMark = m_requirements.init(); reqMark != m_requirements.afterEnd(); reqMark++)
		complexError += (*reqMark).value->getError();

	return complexError;
};
bool BasicInterface::solveComplexReq()
{
	Array<double> arr = getX();

	double secondReqValue, firstReqValue = complexErrValue();

	/*std::cout << "Req value before: " << firstReqValue << std::endl;*/

	double lambda = 0.1;
	while (firstReqValue > 1e-2)
	{
		Array<double> devArr, newArr;

		firstReqValue = complexErrValue();

		int i = 0;
		for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
		{
			devArr.add(complexPartDerivative(i));   //���������� ������ ����������� 
		};

		i = 0;
		for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
		{
			newArr.add(arr[i] - lambda * devArr[i]);   //���������� ����� ������ ���������
		};

		setX(newArr);

		secondReqValue = complexErrValue();
		/*std::cout << secondReqValue << " " << firstReqValue << "\n";*/
		if (secondReqValue > firstReqValue)   //���� �������� �� ����������
		{
			setX(arr);
			lambda = lambda / 2;
		}
		else
		{
			firstReqValue = secondReqValue;
			i = 0;
			for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
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
	Array<double> arr = getX();

	if (arr.getSize() <= varNumber)
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
Array<ID> BasicInterface::ReceiveIdObjects()
{
	Array<ID> IDs;
	for (TreeDict<ID, Point>::Marker mark = m_points.init();mark != m_points.afterEnd(); mark++)
	{
		IDs.add((*mark).key);
	}
	for (TreeDict<ID, Segment>::Marker mark = m_segments.init();mark != m_segments.afterEnd(); mark++)
	{
		IDs.add((*mark).key);
	}
	for (TreeDict<ID, Circle>::Marker mark = m_circles.init();mark != m_circles.afterEnd(); mark++)
	{
		IDs.add((*mark).key);
	}
	return IDs;
}
