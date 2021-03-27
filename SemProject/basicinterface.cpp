//#pragma once
//#include "basicinterface.h"
//#include <iostream>
//
//BasicInterface::BasicInterface()
//{
//
//};
//
//ID  BasicInterface::addObject(ObjType ot)
//{
//    ID id = ID::generateID();
//    switch (ot) {
//    case OT_POINT:
//        m_points.add(id,Point());
//        break;
//    case OT_SEGMENT:
//        m_segments.add(id,Segment());
//        break;
//    case OT_CIRCLE:
//        m_circles.add(id,Circle());
//        break;
//    }
//    return id;
//
//};
//bool BasicInterface::removeObject(ID id) {
//    for (size_t k = 0; k < m_points.getSize();++k) {
//        if (m_points.getChemuByIdx(k) == id) {
//            m_points.removeElementByIdx(k);
//            return true;
//        }
//    }
//    for (size_t k = 0; k < m_segments.getSize();++k) {
//        if (m_segments.getChemuByIdx(k) == id) {
//            m_segments.removeElementByIdx(k);
//            return true;
//        }
//    }
//    for (size_t k = 0; k < m_circles.getSize();++k) {
//        if (m_circles.getChemuByIdx(k) == id) {
//            m_circles.removeElementByIdx(k);
//            return true;
//        }
//    }
//    return false;
//};
//ID  BasicInterface::addRequirement(const Array<ID>& ide, ReqType rt) {
//    ID id = ID::generateID();
//    switch (rt) {
//    case RT_PARALLEL:
//        break;
//    case RT_ORTHO:
//		// ѕроверить что ide - это отрезки
//		// ѕроверить допустимость этого требовани€
//		// !!!
//		// ƒобавить информацию о новом требовании в хранилище        
//        break;
//    case RT_COINCIDE:
//        break;
//    case RT_GROUP:
//        break;
//    case RT_DISTANCE:
//        break;
//    }
//	solveReqs();
//    return id;
//
//};
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
//UniDict<ParamType, double> BasicInterface::queryObjProperties(ID id)
//{//TODO 
//    switch (identifyObjTypeByID(id))
//    {
//    case OT_CIRCLE:
//    {
//        UniDict<ID, Circle>::Marker cm = m_circles.init();
//        while ((*cm).che != id)
//            cm++;
//
//        UniDict<ParamType, double> arr;
//        arr.add(PT_CIRCLE, 4);
//        arr.add(PT_CX, (*cm).cht.center.x);
//        arr.add(PT_CY, (*cm).cht.center.y);
//        arr.add(PT_R, (*cm).cht.r);
//
//        return arr;
//        break;
//    }
//    case OT_POINT:
//    {
//        UniDict<ID, Point>::Marker pm = m_points.init();
//        while ((*pm).che != id)
//            pm++;
//
//        UniDict<ParamType, double> arr;
//        arr.add(PT_POINT, 3);
//        arr.add(PT_PX, (*pm).cht.x);
//        arr.add(PT_PY, (*pm).cht.y);
//
//        return arr;
//        break;
//
//    }
//    case OT_SEGMENT:
//    {
//        UniDict<ID, Segment>::Marker sm = m_segments.init();
//        while ((*sm).che != id)
//            sm++;
//
//        UniDict<ParamType, double> arr;
//        arr.add(PT_SEGMENT, 5);
//        arr.add(PT_P1X, (*sm).cht.p1.x);
//        arr.add(PT_P1Y, (*sm).cht.p1.y);
//        arr.add(PT_P2X, (*sm).cht.p2.x);
//        arr.add(PT_P2Y, (*sm).cht.p2.y);
//
//        return arr;
//        break;
//    }
//    case OT_ERROR:
//    {
//        UniDict<ParamType, double> arr;
//        arr.add(PT_ERROR, -1);
//        return arr;
//    }
//    }
//}
//ObjType BasicInterface::identifyObjTypeByID(ID id)
//{
//    UniDict<ID, Point>::Marker pm = m_points.init();
//    while (pm != m_points.afterEnd())
//    {
//        if ((*pm).che == id)
//            return OT_POINT;
//        pm++;
//    };
//    UniDict<ID, Circle>::Marker cm = m_circles.init();
//    while (cm != m_circles.afterEnd())
//    {
//        if ((*cm).che == id)
//            return OT_CIRCLE;
//        cm++;
//    }
//    UniDict<ID, Segment>::Marker sm = m_segments.init();
//    while (sm != m_segments.afterEnd())
//    {
//        if ((*sm).che == id)
//            return OT_CIRCLE;
//        sm++;
//    }
//    return OT_ERROR;
//}
//Array<double> BasicInterface::getX() {
//	Array<double> res;
//	// ѕробежать по точкам, забрать их координаты в res
//    UniDict<ID, Point>::Marker pointMarker = m_points.init();
//    while (pointMarker != m_points.afterEnd())
//    {
//        res.add((*pointMarker).cht.x);
//        res.add((*pointMarker).cht.y);
//        pointMarker++;
//    }
//	// ѕробежать по отрезкам, забрать их координаты в res
//    UniDict<ID, Segment>::Marker segmentMarker = m_segments.init();
//    while (segmentMarker != m_segments.afterEnd())
//    {
//        res.add((*segmentMarker).cht.p1.x);
//        res.add((*segmentMarker).cht.p1.y);
//        res.add((*segmentMarker).cht.p2.x);
//        res.add((*segmentMarker).cht.p2.y);
//        segmentMarker++;
//    }
//	// ѕробежать по окружност€м, забрать их координаты в res
//    UniDict<ID, Circle>::Marker circleMarker = m_circles.init();
//    while (circleMarker != m_circles.afterEnd())
//    {
//        res.add((*circleMarker).cht.center.x);
//        res.add((*circleMarker).cht.center.y);
//        res.add((*circleMarker).cht.r);
//        circleMarker++;
//    }
//
//	return res;
//}
//void BasicInterface::setX(const Array<double>& X) {
//    size_t i = 0;
//    UniDict<ID, Point>::Marker pointMarker = m_points.init();
//    // ѕробежать часть x и задать координаты точек
//    while (pointMarker != m_points.afterEnd())
//    {
//        (*pointMarker).cht.x = X[i];
//        i++;
//        (*pointMarker).cht.y = X[i];
//        i++;
//        pointMarker++;
//    }
//	// ѕробежать часть x и задать координаты отрезков
//    UniDict<ID, Segment>::Marker segmentMarker = m_segments.init();
//    while (segmentMarker != m_segments.afterEnd())
//    {
//        (*segmentMarker).cht.p1.x = X[i];
//        i++;
//        (*segmentMarker).cht.p1.y = X[i];
//        i++;
//        (*segmentMarker).cht.p2.x = X[i];
//        i++;
//        (*segmentMarker).cht.p2.y = X[i];
//        i++;
//        segmentMarker++;
//    }
//	// ѕробежать часть x и задать координаты окружностей
//    UniDict<ID, Circle>::Marker circleMarker = m_circles.init();
//    while (circleMarker != m_circles.afterEnd())
//    {
//        (*circleMarker).cht.center.x = X[i];
//        i++;
//        (*circleMarker).cht.center.y = X[i];
//        i++;
//        (*circleMarker).cht.r = X[i];
//        i++;
//        segmentMarker++;
//    }
//}
//double BasicInterface::ReqOrtho(ID idSegement1, ID idSegement2)
//{
//    UniDict<ID, Segment>::Marker mark;
//
//    if ((identifyObjTypeByID(idSegement1) != OT_SEGMENT) || (identifyObjTypeByID(idSegement2) != OT_SEGMENT))
//        return -1;
//    
//    mark = m_segments.init();
//    while ((*mark).che != idSegement1)
//        mark++;
//    Segment& l1 = (*mark).cht;
//
//    mark = m_segments.init();
//    while ((*mark).che != idSegement2)
//        mark++;
//    Segment& l2 = (*mark).cht;
//
//    double A1 = l1.p1.x - l1.p2.x;
//    double B1 = l1.p1.y - l1.p2.y;
//    double A2 = l2.p1.x - l2.p2.x;
//    double B2 = l2.p1.y - l2.p2.y;
//
//    return abs(A1 * A2 + B1 * B2);
//};
//double  BasicInterface::partDerivative(Array<double>& arr, int varNumber, ID id1, ID id2)
//{
//    if (arr.getSize() <= varNumber)
//        return 0;
//    double delta = 0.00000000000001;
//    double var = arr[varNumber];
//    double y1 = ReqOrtho(id1, id2);
//    if (y1 == -1)
//        return 0;
//    arr[varNumber] = var + delta;
//    setX(arr);
//    double y2 = ReqOrtho(id1, id2);
//    if (y2 == -1)
//        return 0;
//    arr[varNumber] = var;
//    return (y2 - y1) / delta;
//}
//
//double BasicInterface::calcError() 
//{
//
//    return 1;
//}
//
//bool BasicInterface::solveReqs() 
//{
//    UniDict<ID, Requirement>::Marker reqMark = m_requirements.init();
//    while (reqMark != m_requirements.afterEnd())
//    {
//       
//        if ((*reqMark).cht.type == RT_ORTHO)
//        {
//            Array<ID>::Marker m = (*reqMark).cht.objs.init();
//            while (m != (*reqMark).cht.objs.afterEnd())/////////////////
//            {
//                ID id1, id2;
//                id1 = *m;
//                m++;
//                id2 = *m;
//                //////////////////////////////////
//            }
//        }
//       
//       
//        reqMark++;
//    }
//    return 1;
//}
