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
    for (size_t k = 0; k < m_points.getSize();++k) {
        if (m_points.getChemuByIdx(k) == id) {
            m_points.removeElementByIdx(k);
            return true;
        }
    }
    for (size_t k = 0; k < m_segments.getSize();++k) {
        if (m_segments.getChemuByIdx(k) == id) {
            m_segments.removeElementByIdx(k);
            return true;
        }
    }
    for (size_t k = 0; k < m_circles.getSize();++k) {
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
		// ѕроверить что ide - это отрезки
		// ѕроверить допустимость этого требовани€
		// !!!
		// ƒобавить информацию о новом требовании в хранилище        
        break;
    case RT_COINCIDE:
        break;
    case RT_GROUP:
        break;
    case RT_DISTANCE:
        break;
    }
	solveReqs();
    return id;

};
bool BasicInterface::removeRequirement(ID id) {
    for (size_t k = 0; k < m_requirements.getSize();++k) {
        if (m_requirements.getChemuByIdx(k) == id) {
            m_requirements.removeElementByIdx(k);
            return true;
        }
    }
    return false;
};
UniDict<ParamType, double> BasicInterface::queryObjProperties(ID id)
{//TODO 
    switch (identifyObjTypeByID(id))
    {
    case OT_CIRCLE:
    {
        UniDict<ID, Circle>::Marker cm = m_circles.init();

        
        for (; (*cm).che != id || cm != m_circles.afterEnd() ; cm++)
        {
            
        }
        UniDict<ParamType, double>;
        ParamType obj;

        obj.type = ParamType::PT_CIRCLE;
        obj.value = 4;
        arr.add(obj);

        obj.type = Parameter::PT_CX;
        obj.value = (*cm).obj.center.x;
        arr.add(obj);

        obj.type = Parameter::PT_CY;
        obj.value = (*cm).obj.center.y;
        arr.add(obj);

        obj.type = Parameter::PT_R;
        obj.value = (*cm).obj.r;
        arr.add(obj);

        return arr;
        break;
    }
    case OT_POINT:
    {
        Array<Identifiable<Point> >::Marker pm = m_points.init();
        while (pm != m_points.afterEnd())
            pm++;

        Array<Parameter> arr;
        Parameter obj;

        obj.type = Parameter::PT_POINT;
        obj.value = 3;
        arr.add(obj);

        obj.type = Parameter::PT_PX;
        obj.value = (*pm).obj.x;
        arr.add(obj);

        obj.type = Parameter::PT_PY;
        obj.value = (*pm).obj.y;
        arr.add(obj);

        return arr;
        break;

    }
    case OT_SEGMENT:
    {
        Array<Identifiable<Segment> >::Marker sm = m_segments.init();
        while (sm != m_segments.afterEnd())
            sm++;

        Array<Parameter> arr;
        Parameter obj;

        obj.type = Parameter::PT_SEGMENT;
        obj.value = 5;
        arr.add(obj);

        obj.type = Parameter::PT_P1X;
        obj.value = (*sm).obj.p1.x;
        arr.add(obj);

        obj.type = Parameter::PT_P1Y;
        obj.value = (*sm).obj.p1.y;
        arr.add(obj);

        obj.type = Parameter::PT_P2X;
        obj.value = (*sm).obj.p2.x;
        arr.add(obj);

        obj.type = Parameter::PT_P1X;
        obj.value = (*sm).obj.p2.y;
        arr.add(obj);

        return arr;

        break;
    }
    case OT_ERROR:
    {
        Array<Parameter> arr;
        Parameter err;
        err.type = Parameter::PT_ERROR;
        arr.add(err);
        return arr;
    }
    }
}
ObjType BasicInterface::identifyObjTypeByID(ID id)
{
    UniDict<ID, Point>::Marker pm = m_points.init();
    while (pm != m_points.afterEnd())
    {
        if ((*pm).che == id)
            return OT_POINT;
        pm++;
    };
    UniDict<ID, Circle>::Marker cm = m_circles.init();
    while (cm != m_circles.afterEnd())
    {
        if ((*cm).che == id)
            return OT_CIRCLE;
        cm++;
    }
    UniDict<ID, Segment>::Marker sm = m_segments.init();
    while (sm != m_segments.afterEnd())
    {
        if ((*sm).che == id)
            return OT_CIRCLE;
        sm++;
    }
    return OT_ERROR;
}

Array<double> BasicInterface::getX() {
	Array<double> res;
	// ѕробежать по точкам, забрать их координаты в res
	// ѕробежать по отрезкам, забрать их координаты в res
	// ѕробежать по окружност€м, забрать их координаты в res
	return res;
}
void BasicInterface::setX(const Array<double>&x) {
	// ѕробежать часть x и задать координаты точек
	// ѕробежать часть x и задать координаты отрезков
	// ѕробежать часть x и задать координаты окружностей

}
double BasicInterface::calcError(const Array<double>&x) {
	setX(x)
	for (Dict<ID, Requirement>::Marker m = m_requirements.init(); m != m_requirements.afterEnd(); m++) {
			if ((*m).type == RT_ORTHO) {
				ReqOrtho req;
				req.idSegement1 = (*m).objs[0];
				req.idSegement2 = (*m).objs[1];
				std::cout << "Ortho error " << req.error() << std::endl;
				return req.error();
			}
		}

}

bool BasicInterface::solveReqs() {
}
