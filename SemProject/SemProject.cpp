
#include <iostream>
using namespace std;

enum Colors
{
    COL_RED,
    COL_GREEN,
    COL_BLUE
};

struct Point
{
    //Colors color;
    int x;
    int y;
};

struct Segment
{
    //Colors color;
    Point p1;
    Point p2;
};

struct Circle
{
    //Colors color;
    Point center;
    int r;
};

class PointList
{
private:
    size_t size;
    Point* data;
    PointList* next;

public:
    PointList()
    {
        size = 0;
        data = nullptr;
        next = nullptr;
    }
   
    void addPoint(Point* val2add)
    {
        if (data == nullptr)
        {
            size = 1;
            data = val2add;
            next = new PointList;
        }
        else
        {
            PointList* marker = next;
            while (marker->data != nullptr)
            {
                marker = marker->next;
            }
            marker->data = val2add;
            marker->next = new PointList;
            size++;
        }
    }
    size_t getSize() const { return size; }
    Point getElementByInd(size_t index) const
    {
        if (size <= index)
        {
            cout << "Неверный индекс";
            exit(1);
        }
        if (index == 0)
            return *data;
        PointList* marker = next;
        for (size_t i = 2; i < size; i++)
        {
            marker = marker->next;
        }
        return *marker->data;
    }
};

class SegmentList
{
private:
    size_t size;
    Segment* data;
    SegmentList* next;

public:
    SegmentList()
    {
        size = 0;
        data = nullptr;
        next = nullptr;
    }

    void addSegment(Segment* val2add)
    {
        if (data == nullptr)
        {
            size = 1;
            data = val2add;
            next = new SegmentList;
        }
        else
        {
            SegmentList* marker = next;
            while (marker->data != nullptr)
            {
                marker = marker->next;
            }
            marker->data = val2add;
            marker->next = new SegmentList;
            size++;
        }
    }
    size_t getSize() const { return size; }
    Segment getElementByInd(size_t index) const
    {
        if (size <= index)
        {
            cout << "Неверный индекс";
            exit(1);
        }
        if (index == 0)
            return *data;
        SegmentList* marker = next;
        for (size_t i = 2; i < size; i++)
        {
            marker = marker->next;
        }
        return *marker->data;
    }
};

class CircleList
{
private:
    size_t size;
    Circle* data;
    CircleList* next;

public:
    CircleList()
    {
        size = 0;
        data = nullptr;
        next = nullptr;
    }

    void addCircle(Circle* val2add)
    {
        if (data == nullptr)
        {
            size = 1;
            data = val2add;
            next = new CircleList;
        }
        else
        {
            CircleList* marker = next;
            while (marker->data != nullptr)
            {
                marker = marker->next;
            }
            marker->data = val2add;
            marker->next = new CircleList;
            size++;
        }
    }
    size_t getSize() const { return size; }
    Circle getElementByInd(size_t index) const
    {
        if (size <= index)
        {
            cout << "Неверный индекс";
            exit(1);
        }
        if (index == 0)
            return *data;
        CircleList* marker = next;
        for (size_t i = 2; i < size; i++)
        {
            marker = marker->next;
        }
        return *marker->data;
    }
};

void outputPoints(const PointList* array)
{
    for (size_t k = 0; k < array->getSize(); ++k)
    {
        // Output single point
        std::cout << array->getElementByInd(k).x << " " << array->getElementByInd(k).y << std::endl;
    }
}
bool testPointArrayCreation()
{
    PointList list;
    if (list.getSize() == 0)
        return true;
    return false;
}

bool testPointArraySize()
{
    PointList list;
    Point p1 = { 1, 2 };
    list.addPoint(&p1);
    if (list.getSize() != 1)
        return false;
    return true;
}

bool testPointArrayAccess1()
{
    PointList list;
    Point p1 = { 1, 2 };
    list.addPoint(&p1);
    Point p2 = list.getElementByInd(0);
    if (p1.x == p2.x && p1.y == p2.y)
        return true;
    return false;
}

bool testPointArrayAccessN()
{
    PointList list;
    Point p1 = { 1, 2 };
    list.addPoint(&p1);
    Point p2 = { 2, 2 };
    list.addPoint(&p2);
    Point p3 = { 4, 2 };
    list.addPoint(&p3);

    Point pp = list.getElementByInd(2);
    if (pp.x == p3.x && pp.y == p3.y)
        return true;
    return false;
}

void runAllTests()
{
    std::cout << "testPointArrayCreation() " << (testPointArrayCreation() ? "passed" : "failed") << std::endl;
    std::cout << "testPointArraySize() " << (testPointArraySize() ? "passed" : "failed") << std::endl;
    std::cout << "testPointArrayAccess1() " << (testPointArrayAccess1() ? "passed" : "failed") << std::endl;
    std::cout << "testPointArrayAccessN() " << (testPointArrayAccessN() ? "passed" : "failed") << std::endl;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    runAllTests();
    PointList pointList;

    Point p1;
    p1.x = 1;
    p1.y = 2;
    pointList.addPoint(&p1);
    Point p2 = { 2, 3 };
    pointList.addPoint(&p2);
    Point p3 = { 5, 3 };
    pointList.addPoint(&p3);
    Point p4 = { 6, 4 };
    pointList.addPoint(&p4);

    outputPoints(&pointList);
    system("pause");
    return 0;
}
