#pragma once

#include "objects.h"
#include "Array.h"
#include "List.h"
#include "Dict.h"

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
  /*  bool changeObjectProperty(ID);*/
    ID addRequirement(const Array<ID>&, ReqType, double dist = 0);
    UniDict<ParamType, double> queryObjProperties(ID);
    ObjType identifyObjTypeByID(ID);
    void showRequirements();    //Нужно для теста
    bool removeRequirementByID(ID);
    void solveReq(ID id1, ID id2, ReqType rt, double distance=0);
   
 
private:

    UniDict<ID, Point> m_points;
    UniDict<ID, Circle> m_circles;
    UniDict<ID, Segment> m_segments;
    UniDict<ID, Requirement> m_requirements;

    double ReqValue(ID idSegement1, ID idSegement2, ReqType rt, double distance=0);
    double partDerivative(int varNumber, ID id1, ID id2, ReqType rt, double distance=0);
	Array<double> getX();
	void setX(const Array<double>&x);
	bool solveReqs();


};


