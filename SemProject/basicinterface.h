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
   /* ID addObject(ObjType, const Array<Parameter>&);*/
    bool removeObject(ID);
  /*  bool changeObjectProperty(ID);*/
    ID  addRequirement(const Array<ID>&, ReqType);
    UniDict<ParamType, double> queryObjProperties(ID);
    ObjType identifyObjTypeByID(ID);
    bool removeRequirement(ID);
    void solveOrtho(Array<double>& arr, ID id1, ID id2);
    Array<double> getX();
    void setX(const Array<double>& x);
private:

    UniDict<ID, Point> m_points;
    UniDict<ID, Circle> m_circles;
    UniDict<ID, Segment> m_segments;
    UniDict<ID, Requirement> m_requirements;

    double ReqOrtho(ID idSegement1, ID idSegement2);
    double partOrthoDerivative(Array<double>& arr, int varNumber, ID id1, ID id2);
	//Array<double> getX();
	//void setX(const Array<double>&x);
	bool solveReqs();


};


