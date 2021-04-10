#pragma once
#include "basicinterface.h"
#include <iostream>

BasicInterface::BasicInterface()
{

};

ID  BasicInterface::addObject(ObjType ot)
{
    ID id = ID::generateID();
    switch (ot) {
    case OT_POINT:
        m_points.add(id,Point());
        break;
    case OT_SEGMENT:
        m_segments.add(id,Segment());
        break;
    case OT_CIRCLE:
        m_circles.add(id,Circle());
        break;
    }
    return id;
};
bool BasicInterface::removeObject(ID id) {
    for (size_t k = 0; k < m_points.getSize(); ++k) {
        if (m_points.getChemuByIdx(k) == id) {
            m_points.removeElementByIdx(k);
            return true;
        }
    }
    for (size_t k = 0; k < m_segments.getSize(); ++k) {
        if (m_segments.getChemuByIdx(k) == id) {
            m_segments.removeElementByIdx(k);
            return true;
        }
    }
    for (size_t k = 0; k < m_circles.getSize(); ++k) {
        if (m_circles.getChemuByIdx(k) == id) {
            m_circles.removeElementByIdx(k);
            return true;
        }
    }
    return false;
};
ID  BasicInterface::addRequirement(const Array<ID>& ide, ReqType rt) {
    ID id = ID::generateID();
    switch (rt) {
    case RT_PARALLEL:
        break;
    case RT_ORTHO:
        break;
    case RT_COINCIDE:
        break;
    case RT_GROUP:
        break;
    case RT_DISTANCE:
        break;
    }
	
    return id;

};
//bool BasicInterface::removeRequirement(ID id) {
//
//    for (size_t k = 0; k < m_requirements.getSize();++k) {
//        if (m_requirements.getChemuByIdx(k) == id) {
//            m_requirements.removeElementByIdx(k);
//            return true;
//        }
//    }
//    return false;
//};
UniDict<ParamType, double> BasicInterface::queryObjProperties(ID id)
{
    switch (identifyObjTypeByID(id))
    {
    case OT_CIRCLE:
    {
        UniDict<ID, Circle>::Marker cm = m_circles.init();
        while ((*cm).key != id)
            cm++;

        UniDict<ParamType, double> arr;
        arr.add(PT_CIRCLE, 4);
        arr.add(PT_CX, (*cm).val.center.x);
        arr.add(PT_CY, (*cm).val.center.y);
        arr.add(PT_R, (*cm).val.r);

        return arr;
        break;
    }
    case OT_POINT:
    {
        UniDict<ID, Point>::Marker pm = m_points.init();
        while ((*pm).key != id)
            pm++;

        UniDict<ParamType, double> arr;
        arr.add(PT_POINT, 3);
        arr.add(PT_PX, (*pm).val.x);
        arr.add(PT_PY, (*pm).val.y);

        return arr;
        break;

    }
    case OT_SEGMENT:
    {
        UniDict<ID, Segment>::Marker sm = m_segments.init();
        while ((*sm).key != id)
            sm++;

        UniDict<ParamType, double> arr;
        arr.add(PT_SEGMENT, 5);
        arr.add(PT_P1X, (*sm).val.p1.x);
        arr.add(PT_P1Y, (*sm).val.p1.y);
        arr.add(PT_P2X, (*sm).val.p2.x);
        arr.add(PT_P2Y, (*sm).val.p2.y);

        return arr;
        break;
    }
    default:
    {
        UniDict<ParamType, double> arr;
        arr.add(PT_ERROR, -1);
        return arr;
    }

    }
}
ObjType BasicInterface::identifyObjTypeByID(ID id)
{
    UniDict<ID, Point>::Marker pm = m_points.init();
    while (pm != m_points.afterEnd())
    {
        if ((*pm).key == id)
            return OT_POINT;
        pm++;
    };
    UniDict<ID, Circle>::Marker cm = m_circles.init();
    while (cm != m_circles.afterEnd())
    {
        if ((*cm).key == id)
            return OT_CIRCLE;
        cm++;
    }
    UniDict<ID, Segment>::Marker sm = m_segments.init();
    while (sm != m_segments.afterEnd())
    {
        if ((*sm).key == id)
            return OT_SEGMENT;
        sm++;
    }
    return OT_ERROR;
}
Array<double> BasicInterface::getX() {
	
    Array<double> res;
	
    UniDict<ID, Point>::Marker pointMarker = m_points.init();
    while (pointMarker != m_points.afterEnd())
    {
        res.add((*pointMarker).val.x);
        res.add((*pointMarker).val.y);
        pointMarker++;
    }
	 
    UniDict<ID, Segment>::Marker segmentMarker = m_segments.init();
    while (segmentMarker != m_segments.afterEnd())
    {
        res.add((*segmentMarker).val.p1.x);
        res.add((*segmentMarker).val.p1.y);
        res.add((*segmentMarker).val.p2.x);
        res.add((*segmentMarker).val.p2.y);
        segmentMarker++;
    }
	 
    UniDict<ID, Circle>::Marker circleMarker = m_circles.init();
    while (circleMarker != m_circles.afterEnd())
    {
        res.add((*circleMarker).val.center.x);
        res.add((*circleMarker).val.center.y);
        res.add((*circleMarker).val.r);
        circleMarker++;
    }

	return res;
}
void BasicInterface::setX(const Array<double>& X) {
    size_t i = 0;
    UniDict<ID, Point>::Marker pointMarker = m_points.init();
     
    while (pointMarker != m_points.afterEnd())
    {
        (*pointMarker).val.x = X[i];
        i++;
        (*pointMarker).val.y = X[i];
        i++;
        pointMarker++;
    }
	
    UniDict<ID, Segment>::Marker segmentMarker = m_segments.init();
    while (segmentMarker != m_segments.afterEnd())
    {
        (*segmentMarker).val.p1.x = X[i];
        i++;
        (*segmentMarker).val.p1.y = X[i];
        i++;
        (*segmentMarker).val.p2.x = X[i];
        i++;
        (*segmentMarker).val.p2.y = X[i];
        i++;
        segmentMarker++;
    }
	 
    UniDict<ID, Circle>::Marker circleMarker = m_circles.init();
    while (circleMarker != m_circles.afterEnd())
    {
        (*circleMarker).val.center.x = X[i];
        i++;
        (*circleMarker).val.center.y = X[i];
        i++;
        (*circleMarker).val.r = X[i];
        i++;
        segmentMarker++;
    }
}



double BasicInterface::ReqValue(ID id1, ID id2, ReqType rt, double distance)
{
    ObjType ot1, ot2;
    ot1 = identifyObjTypeByID(id1);
    ot2 = identifyObjTypeByID(id2);

    if (rt == RT_PARALLEL)
    {
        if ((ot1 != OT_SEGMENT) || (ot2 != OT_SEGMENT))
            return -1;

        UniDict<ID, Segment>::Marker mark;
        mark = m_segments.init();
        while ((*mark).key != id1)
            mark++;
        Segment& l1 = (*mark).val;

        mark = m_segments.init();
        while ((*mark).key != id2)
            mark++;
        Segment& l2 = (*mark).val;

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
    else if (rt == RT_ORTHO)
    {

        if ((ot1 != OT_SEGMENT) || (ot2 != OT_SEGMENT))
            return -1;


        UniDict<ID, Segment>::Marker mark;
        mark = m_segments.init();
        while ((*mark).key != id1)
            mark++;
        Segment& l1 = (*mark).val;

        mark = m_segments.init();
        while ((*mark).key != id2)
            mark++;
        Segment& l2 = (*mark).val;

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
            UniDict<ID, Point>::Marker mark;
            mark = m_points.init();
            while ((*mark).key != id1)
                mark++;
            Point& p1 = (*mark).val;

            mark = m_points.init();
            while ((*mark).key != id2)
                mark++;
            Point& p2 = (*mark).val;

            return abs(distance - sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
        }
        else if ((ot1 == OT_POINT) && (ot2 == OT_SEGMENT)) //point and line
        {
            UniDict<ID, Point>::Marker mark1;
            mark1 = m_points.init();
            while ((*mark1).key != id1)
                mark1++;
            Point& p = (*mark1).val;

            UniDict<ID, Segment>::Marker mark2;
            mark2 = m_segments.init();
            while ((*mark2).key != id2)
                mark2++;
            Segment& l = (*mark2).val;
           
            double A = l.p2.y - l.p1.y;
            double B = l.p1.x - l.p2.x;
            double C = l.p2.x * l.p1.y - l.p1.x * l.p2.y;

            return abs(distance - abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B));
        }
        else if ((ot2 == OT_POINT) && (ot1 == OT_SEGMENT)) //point and line
        {
            
            UniDict<ID, Point>::Marker mark1;
            mark1 = m_points.init();
            while ((*mark1).key != id2)
                mark1++;
            Point& p = (*mark1).val;

            UniDict<ID, Segment>::Marker mark2;
            mark2 = m_segments.init();
            while ((*mark2).key != id1)
                mark2++;
            Segment& l = (*mark2).val;


            double A = l.p2.y - l.p1.y;
            double B = l.p1.x - l.p2.x;
            double C = l.p2.x * l.p1.y - l.p1.x * l.p2.y;
            return abs(distance - abs(A * p.x + B * p.y + C) / sqrt(A * A + B * B));
        }
        else if ((ot2 == OT_SEGMENT) && (ot1 == OT_SEGMENT)) //2 lines 
        {
            UniDict<ID, Segment>::Marker mark;
            mark = m_segments.init();
            while ((*mark).key != id1)
                mark++;
            Segment& l1 = (*mark).val;

            mark = m_segments.init();
            while ((*mark).key != id2)
                mark++;
            Segment& l2 = (*mark).val;

            if (ReqValue(id1, id2, RT_PARALLEL) <= 0.01)
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

    double req1 = ReqValue(id1, id2, rt, distance);
    if (req1 == -1)
    {
        std::cout << "req1 error\n";
        return 0;
    }

    arr[varNumber] = var + delta;
    setX(arr);

    double req2 = ReqValue(id1, id2, rt, distance);
    if (req2 == -1)
    {
        std::cout << "req2 error\n";
        return 0;
    }

    arr[varNumber] = var;
    setX(arr);

    return (req2 - req1) / delta;
}
void BasicInterface::solveReq(ID id1, ID id2, ReqType rt, double distance)
{
    Array<double> arr = getX();

    double secondReqValue, firstReqValue = ReqValue(id1, id2, rt, distance);

    std::cout << "Req value before: " << firstReqValue << std::endl;

    for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++)
    {
        std::cout << *m << std::endl;
    }

    double lambda = 0.1;

    while (firstReqValue > 0.01)
    {
        Array<double> devArr, newArr;
        
        firstReqValue = ReqValue(id1, id2, rt, distance);
       
        int i = 0;
        for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
        {
            devArr.add(partDerivative(i, id1, id2, rt, distance));   //Составляем вектор производных
        };

        i = 0;
        for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
        {
            newArr.add(arr[i] - lambda * devArr[i]);   //Составляем новый вектор координат
        };

        setX(newArr);

        secondReqValue = ReqValue(id1, id2, rt, distance);
       
        if (secondReqValue > firstReqValue)   //Если ситуация не улучшилась
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
    for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++)
    {
        std::cout << *m << std::endl;
    }
}

bool BasicInterface::solveReqs() 
{
    UniDict<ID, Requirement>::Marker reqMark = m_requirements.init();
    while (reqMark != m_requirements.afterEnd())
    {
       
        if ((*reqMark).val.type == RT_ORTHO)
        {
            Array<ID>::Marker m = (*reqMark).val.objs.init();
            while (m != (*reqMark).val.objs.afterEnd())/////////////////
            {
                ID id1, id2;
                id1 = *m;
                m++;
                id2 = *m;
                ////////////////////////////////
            }
        }
       
       
        reqMark++;
    }
    return 1;
}
