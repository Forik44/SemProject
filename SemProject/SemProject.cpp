#include "Objects.h"
#include "Array.h"
#include <iostream>

using namespace std;

enum Colors
{
    COL_RED,
    COL_GREEN,
    COL_BLUE
};


/*
void outputPoints(const PointList pointStorage)
{
    for (size_t k = 0; k < pointStorage.getSize(); ++k) {
        cout << "( " << pointStorage.getElementByIdx(k).x << " ; " << pointStorage.getElementByIdx(k).y << " )" << endl;
    }
};
void outputPoints(const PointArray pointStorage)
{
    for (size_t k = 0; k < pointStorage.getSize(); ++k) {
        cout << "( " << pointStorage.getElementByIdx(k).x << " ; " << pointStorage.getElementByIdx(k).y << " )" << endl;
    }
};
void outputPoints(const CircleList circleStorage)
{
    for (size_t k = 0; k < circleStorage.getSize(); ++k) {
        cout << "( " << circleStorage.getElementByIdx(k).center.x << " ; " << circleStorage.getElementByIdx(k).center.y << " ) ";
        cout << "R = " << circleStorage.getElementByIdx(k).r << endl;
    }
};
void outputPoints(const CircleArray circleStorage)
{
    for (size_t k = 0; k < circleStorage.getSize(); ++k) {
        cout << "( " << circleStorage.getElementByIdx(k).center.x << " ; " << circleStorage.getElementByIdx(k).center.y << " ) ";
        cout << "R = " << circleStorage.getElementByIdx(k).r << endl;
    }
};
void outputPoints(const SegmentArray segmentStorage)
{
    for (size_t k = 0; k < segmentStorage.getSize(); ++k) {
        cout << "( " << segmentStorage.getElementByIdx(k).p1.x << " ; " << segmentStorage.getElementByIdx(k).p1.y << " ) :";
        cout << "( " << segmentStorage.getElementByIdx(k).p2.x << " ; " << segmentStorage.getElementByIdx(k).p2.y << " ) " << endl;
    }
};
void outputPoints(const SegmentList segmentStorage)
{
    for (size_t k = 0; k < segmentStorage.getSize(); ++k) {
        cout << "( " << segmentStorage.getElementByIdx(k).p1.x << " ; " << segmentStorage.getElementByIdx(k).p1.y << " ) :";
        cout << "( " << segmentStorage.getElementByIdx(k).p2.x << " ; " << segmentStorage.getElementByIdx(k).p2.y << " ) " << endl;
    }
};
*/

void OutputPoints(const Array<Point> pointStorage)
{
    for (size_t k = 0; k < pointStorage.getSize(); ++k) {
        cout << "( " << pointStorage.getElementByIdx(k).x << " ; " << pointStorage.getElementByIdx(k).y << " )" << endl;
    }
}

int main(int argc, char* argv[])
{
    /*runAllTests();*/
    /*
    PointArray pointStorage;
 
    Point p1;
    p1.x = 1;
    p1.y = 2;

    pointStorage.addPoint(p1);
    Point p2 = { 2, 3 };
    pointStorage.addPoint(p2);
    Point p3 = { 5, 3 };
    pointStorage.addPoint(p3);
    Point p4 = { 6, 4 };
    pointStorage.addPoint(p4);
    */
    /*CircleList circleStorage;
    for (int i = 0; i < 5; i++)
    {
        Point p = { i,i };
        Circle tmp = { p, i*i };
        circleStorage.addCircle(tmp);
    }
    SegmentList segmentStorage;
    for (int i = 0; i < 5; i++)
    {
        Point p1 = { i,i };
        Point p2 = { i-1,i+1 };
        Segment tmp = { p1, p2 };
        segmentStorage.addSegment(tmp);
    }
    
    outputPoints(segmentStorage);
    outputPoints(segmentStorage);
    */

    Array<Point> ArrayPoint;
    for (int i = 0; i < 5; i++)
    {
        Point p1 = { i,i };
        ArrayPoint.add(p1);
    }
    OutputPoints(ArrayPoint);
    ArrayPoint.removeByIdx(2);
    OutputPoints(ArrayPoint);

    system("pause");
    return 0;
}
