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
double BasicInterface::ReqOrtho(ID idSegement1, ID idSegement2)
{
    UniDict<ID, Segment>::Marker mark;

    if ((identifyObjTypeByID(idSegement1) != OT_SEGMENT) || (identifyObjTypeByID(idSegement2) != OT_SEGMENT))
        return -1;
    
    mark = m_segments.init();
    while ((*mark).key != idSegement1)
        mark++;
    Segment& l1 = (*mark).val;

    mark = m_segments.init();
    while ((*mark).key != idSegement2)
        mark++;
    Segment& l2 = (*mark).val;

    double A1 = l1.p1.x - l1.p2.x;
    double B1 = l1.p1.y - l1.p2.y;
    double A2 = l2.p1.x - l2.p2.x;
    double B2 = l2.p1.y - l2.p2.y;

    return abs(A1 * A2 + B1 * B2);
};
double  BasicInterface::partOrthoDerivative(Array<double>& arr, int varNumber, ID id1, ID id2)
{
    if (arr.getSize() <= varNumber)
        return 0;

    double delta = 1e-10;
    double var = arr[varNumber];

    double req1 = ReqOrtho(id1, id2);
    if (req1 == -1)
        return 0;

    arr[varNumber] = var + delta;
    setX(arr);

    double req2 = ReqOrtho(id1, id2);
    if (req2 == -1)
        return 0;

    arr[varNumber] = var;
    setX(arr);

    return (req2 - req1) / delta;
}
void BasicInterface::solveOrtho(Array<double>& arr, ID id1, ID id2)
{
    double secondOrtho, firstOrtho = ReqOrtho(id1, id2);
    double lambda = 0.1;
    std::cout << "ReqOrtho before: " << firstOrtho << std::endl;

    while (firstOrtho > 0.01)
    {
        Array<double> devArr, newArr;
        firstOrtho = ReqOrtho(id1, id2);
        system("cls");
        for (Array<double>::Marker m = arr.init(); m.canMoveNext(); m++)
        {
            std::cout << *m << std::endl;
        };

        int i = 0;
        for (Array<double>::Marker m = arr.init(); m.canMoveNext(); m++, i++)
        {
            devArr.add(partOrthoDerivative(arr, i, id1, id2));   //Составляем вектор производных
        };

        i = 0;
        for (Array<double>::Marker m = arr.init(); m.canMoveNext(); m++, i++)
        {
            newArr.add(arr[i] - lambda * devArr[i]);   //Составляем новый вектор координат
        };

        setX(newArr);

        secondOrtho = ReqOrtho(id1, id2);
       
        if (secondOrtho > firstOrtho)   //Если ситуация не улучшилась
        {
            setX(arr);
            lambda = lambda / 10;
        }
        else
        {
            firstOrtho = secondOrtho;
            i = 0;
            for (Array<double>::Marker m = arr.init(); m.canMoveNext(); m++, i++)
            {
                arr[i] = newArr[i];
            };
        }
    }

    std::cout << "ReqOrtho after: " << ReqOrtho(id1, id2) << std::endl;
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
