#include "point_array.h"
#include "point_list.h"
#include "circle_array.h"
#include "circle_list.h"
#include "Tests.h"
#include <iostream>

using namespace std;

enum Colors
{
    COL_RED,
    COL_GREEN,
    COL_BLUE
};

class SegmentArray
{
private:
    size_t size;
    Segment* data;

public:
    SegmentArray()
    {
        size = 0;
        data = nullptr;
    }
    ~SegmentArray()
    {
        if (data != nullptr)
            delete[] data;
    }
    void addSegment(Segment val2add)
    {
        if (size == 0)
        {
            data = new Segment[1];
            data[0] = val2add;
            size = 1;
        }
        else
        {
            Segment* tmp = new Segment[size + 1];
            for (size_t i = 0; i < size; i++)
            {
                tmp[i] = data[i];
            }
            tmp[size] = val2add;
            delete[] data;
            data = tmp;
            size++;
        }
    }
    size_t getSize() const { return size; }
    Segment getElementByIdx(size_t index /*номер элемента*/) const
    {
        if (size <= index)
            //Ошибка !!!
            exit(1);
        else
            return data[index]; // *(data + index)
    }
};

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

int main(int argc, char* argv[])
{
    runAllTests();
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
    CircleList circleStorage;
    for (int i = 0; i < 5; i++)
    {
        Point p = { i,i };
        Circle tmp = { p, i*i };
        circleStorage.addCircle(tmp);
    }
    
    outputPoints(circleStorage);
    outputPoints(circleStorage);
    system("pause");
    return 0;
}
