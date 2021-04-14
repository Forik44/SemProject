#pragma once
#include "basicinterface.h"
#include <iostream>

BasicInterface::BasicInterface()
{

};

ID  BasicInterface::addObject(ObjType ot)
{
    ID id = ID::generateID();
    switch (ot) 
    {
    case OT_POINT:
        Point p;
        p.x = rand() % 5;
        p.y = rand() % 5;
        m_points.add(id, p);
        break;
    case OT_SEGMENT:
        Segment s;
        s.p1.x = rand() % 5;
        s.p1.y = rand() % 5;
        s.p2.x = rand() % 5;
        s.p2.y = rand() % 5;
        m_segments.add(id, s);
        break;
    case OT_CIRCLE:
        Circle c;
        c.center.x = rand() % 5;
        c.center.y = rand() % 5;
        c.r = 1;
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
    for (UniDict<ID, Requirement>::Marker m1 = m_requirements.init(); m1 != m_requirements.afterEnd(); m1++, i++)
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

    for (int i = 0; i < arrID.getSize(); i++)
    {
        m_requirements.removeElementByKey(arrID[i]);
    }

    return false;
};
bool BasicInterface::removeRequirementByID(ID id)
{
    return m_requirements.removeElementByKey(id);
};
ID  BasicInterface::addRequirement(const Array<ID>& idArr, ReqType rt, double dist) 
{
    switch (rt)     //Проверка на валидность требований
    {
    case RT_PARALLEL:
        for (int i = 0; i < idArr.getSize(); i++)
        {
            ID id = idArr[i];
            if (identifyObjTypeByID(id) != OT_SEGMENT)
            {
                std::cout << "Invalid param type for this requirement: RT_PARALLEL\n";
                throw;
            }   
        }
        break;
    case RT_ORTHO:
        for (int i = 0; i < idArr.getSize(); i++)
        {
            if (identifyObjTypeByID(idArr[i]) != OT_SEGMENT)
            {
                std::cout << "Invalid param type for this requirement: RT_ORTHO\n";
                throw;
            }
        }
        break;
    case RT_COINCIDE:
        std::cout << "RT_COINCIDE hasn't added yet\n";
        throw;
        break;
    case RT_GROUP:
        std::cout << "RT_GROUP hasn't added yet\n";
        throw;
        break;
    case RT_DISTANCE:
        for (int i = 0; i < idArr.getSize(); i++)
        {
            if (!((identifyObjTypeByID(idArr[i]) == OT_SEGMENT) || (identifyObjTypeByID(idArr[i]) == OT_POINT)))
            {
                std::cout << "Invalid param type for this requirement: RT_DISTANCE\n";
                throw;
            }
        }
        
        break;
    }

    ID id1, id;
    Requirement req;
    req.objs = idArr;
    req.type = rt;
    id = id1.generateID();
    m_requirements.add(id, req);
    return id;

};
void  BasicInterface::showRequirements()
{
    if (m_requirements.getSize() == 0)
    {
        std::cout << "No requirements\n";
        return;
    }

    for (UniDict<ID, Requirement>::Marker mark = m_requirements.init(); mark != m_requirements.afterEnd(); mark++)
    {
        std::cout << "Requirement ID: " << (*mark).key.getID() << std::endl;
        std::cout << "Requirement type: " << (*mark).val.type << std::endl;
        std::cout << "Objects ID: ";
        for (Array<ID>::Marker m = (*mark).val.objs.init(); m != (*mark).val.objs.afterEnd(); m++)
        {
            std::cout << (*m).getID() << " ";
        }
        std::cout << "\n";
    }
    

};
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
Array<double> BasicInterface::getX() 
{
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
void BasicInterface::setX(const Array<double>& X) 
{
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
double BasicInterface::particularErrValue(ID id1, ID id2, ReqType rt, double distance)
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
            devArr.add(partDerivative(i, id1, id2, rt, distance));   //Составляем вектор производных
        };

        i = 0;
        for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
        {
            newArr.add(arr[i] - lambda * devArr[i]);   //Составляем новый вектор координат
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

    for (UniDict<ID, Requirement>::Marker reqMark = m_requirements.init(); reqMark != m_requirements.afterEnd(); reqMark++)
    {
        ReqType rt = (*reqMark).val.type;
        Array<ID> idArr = (*reqMark).val.objs;
        for (int i = 1; i < idArr.getSize(); i++)
        {
            complexError += particularErrValue(idArr[0], idArr[i], rt);
        }
    }

    return complexError;
};
bool BasicInterface::solveComplexReq() 
{
    Array<double> arr = getX();

    double secondReqValue, firstReqValue = complexErrValue();

    std::cout << "Req value before: " << firstReqValue << std::endl;

    double lambda = 0.1;
    while (firstReqValue > 1e-7)
    {
        Array<double> devArr, newArr;

        firstReqValue = complexErrValue();

        int i = 0;
        for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
        {
            devArr.add(complexPartDerivative(i));   //Составляем вектор производных 
        };

        i = 0;
        for (Array<double>::Marker m = arr.init(); m != arr.afterEnd(); m++, i++)
        {
            newArr.add(arr[i] - lambda * devArr[i]);   //Составляем новый вектор координат
        };

        setX(newArr);

        secondReqValue = complexErrValue();

        if (secondReqValue > firstReqValue)   //Если ситуация не улучшилась
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

    std::cout << "Req value after: " << firstReqValue << std::endl;
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
