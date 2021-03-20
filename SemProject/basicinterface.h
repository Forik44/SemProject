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

private:

    UniDict<ID, Point> m_points;
    UniDict<ID, Circle> m_circles;
    UniDict<ID, Segment> m_segments;
    UniDict<ID, Requirement> m_requirements;

   /* Array<Identifiable<Point>> m_points;
    Array<Identifiable<Segment> > m_segments;
    Array<Identifiable<Circle> > m_circles;

    List<Identifiable<Point>> l_points;
    List<Identifiable<Segment>> l_segmentss;
    List<Identifiable<Circle>> l_circles;
  
    Array<Identifiable<Requirement> > m_requirements;
      */
	struct ReqOrtho
	{
		ID idSegement1;
		ID idSegement2;
        UniDict<ID, Segment> *segments;
		double error()
		{
			
			Segment &l1 = (*segments)[idSegement1];
			Segment &l2 = (*segments)[idSegement2];

			double A1 = l1.p1.x - l1.p2.x;
			double B1 = l1.p1.y - l1.p2.y;
			double A2 = l2.p1.x - l2.p2.x;
			double B2 = l2.p1.y - l2.p2.y;

			return abs(A1 * A2 + B1 * B2);

		}
	};

	Array<double> BasicInterface::getX();
	void BasicInterface::setX(const Array<double>&x);
	double BasicInterface::calcError(const Array<double>&x);
	bool BasicInterface::solveReqs();


};


