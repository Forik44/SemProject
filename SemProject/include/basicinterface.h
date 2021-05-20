#pragma once

#include "objects.h"
#include "Array.h"
#include "List.h"
#include "Dict.h"
#include "IReq.h"
#include "TreeDict.h"

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
    BasicInterface(const BasicInterface& original);
    ~BasicInterface();
    ID addObject(ObjType);
    bool removeObjectByID(ID);
    TreeDict<ParamType, double> queryObjProperties(ID);
    ObjType identifyObjTypeByID(ID);
    void showRequirements();    //Нужно для теста
    bool removeRequirementByID(ID);
    bool solveComplexReq();
    void solveParticularReq(ID id1, ID id2, ReqType rt, double distance = 0);
    Array<ID>& addRequirement(const Array<ID>& idArr, ReqType rt, double distance = 0);
    Array<ID> ReceiveIdObjects();
private:

    TreeDict<ID, Point> m_points;
    TreeDict<ID, Circle> m_circles;
    TreeDict<ID, Segment> m_segments;
    TreeDict<ID, IReq*> m_requirements;

    double particularErrValue(ID idSegement1, ID idSegement2, ReqType rt, double distance=0);
    double complexErrValue();
    double partDerivative(int varNumber, ID id1, ID id2, ReqType rt, double distance=0);
	Array<double> getX();
	void setX(const Array<double>&x);
    double complexPartDerivative(int varNumber);


};


