#pragma once

#include "objects.h"
//#include "Array.h"
#include <vector>
#include "List.h"
#include "Dict.h"
#include "IReq.h"
//#include "TreeDict.h"
#include <map>
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
    BasicInterface(const BasicInterface& original) = delete;
    ~BasicInterface(){};
    ID addObject(ObjType);
    bool removeObjectByID(ID);
    std::map<ParamType, double> queryObjProperties(ID);
    ObjType identifyObjTypeByID(ID);
    void showRequirements();    //Нужно для теста
    bool removeRequirementByID(ID);
    bool solveComplexReq();
    void solveParticularReq(ID id1, ID id2, ReqType rt, double distance = 0);
    std::vector<ID>& addRequirement(const std::vector<ID>& idArr, ReqType rt, double distance = 0);
    std::vector<ID> ReceiveIdObjects();
private:

    std::map<ID, Point> m_points;
    std::map<ID, Circle> m_circles;
    std::map<ID, Segment> m_segments;
    std::map<ID, IReq*> m_requirements;

    double particularErrValue(ID idSegement1, ID idSegement2, ReqType rt, double distance=0);
    double complexErrValue();
    double partDerivative(int varNumber, ID id1, ID id2, ReqType rt, double distance=0);
    std::vector <double> getX();
    void setX(const std::vector<double>&x);
    double complexPartDerivative(int varNumber);


};


