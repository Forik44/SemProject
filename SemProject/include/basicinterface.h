#pragma once

#include "objects.h"
#include "Array.h"
#include "List.h"
#include "Dict.h"
#include "IReq.h"

enum ParamType
{
    PT_ERROR,
    PT_POINT,
    PT_CIRCLE,
    PT_SEGMENT,
    PT_CX,
    PT_CY,
    PT_R,
    PT_P1X,
    PT_P2X,
    PT_P1Y,
    PT_P2Y,
    PT_PX,
    PT_PY
};

class BasicInterface
{
public:
    BasicInterface();
    ID addObject(ObjType);
    bool removeObjectByID(ID);
    UniDict<ParamType, double> queryObjProperties(ID);
    ObjType identifyObjTypeByID(ID);
    void showRequirements();    //Нужно для теста
    bool removeRequirementByID(ID);
    bool solveComplexReq();
    void solveParticularReq(ID id1, ID id2, ReqType rt, double distance = 0);
    Array<ID>& addRequirement(const Array<ID>& idArr, ReqType rt, double distance = 0);
    Array<ID> ReceiveIdObjects();
private:

    UniDict<ID, Point> m_points;
    UniDict<ID, Circle> m_circles;
    UniDict<ID, Segment> m_segments;
    UniDict<ID, IReq*> m_requirements;

    double particularErrValue(ID idSegement1, ID idSegement2, ReqType rt, double distance=0);
    double complexErrValue();
    double partDerivative(int varNumber, ID id1, ID id2, ReqType rt, double distance=0);
	Array<double> getX();
	void setX(const Array<double>&x);
    double complexPartDerivative(int varNumber);


};


