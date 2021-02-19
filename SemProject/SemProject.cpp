
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

class PointArray
{
private:
    size_t m_size;
    Point* data;

public:
    PointArray()
    {
        m_size = 0;
        data = nullptr;
    }
    ~PointArray()
    {
        if (data != nullptr)
            delete[] data;
    }
    void addPoint(Point val2add)
    {
        if (m_size == 0)
        {
            data = new Point[1];
            data[0] = val2add;
            m_size = 1;
        }
        else
        {
            Point* tmp = new Point[m_size + 1];
            for (size_t i = 0; i < m_size; i++)
            {
                tmp[i] = data[i];
            }
            tmp[m_size] = val2add;
            delete[] data;
            data = tmp;
            m_size++;
        }
    }
    size_t getSize() const { return m_size; }
    Point getElementByInd(size_t index /*номер элемента*/) const
    {
        if (m_size <= index)
            //Ошибка !!!
            exit(1);
        else
            return data[index]; // *(data + index)
    }
};

class SegmentArray
{
private:
    size_t m_size;
    Segment* data;

public:
    SegmentArray()
    {
        m_size = 0;
        data = nullptr;
    }
    ~SegmentArray()
    {
        if (data != nullptr)
            delete[] data;
    }
    void addSegment(Segment val2add)
    {
        if (m_size == 0)
        {
            data = new Segment[1];
            data[0] = val2add;
            m_size = 1;
        }
        else
        {
            Segment* tmp = new Segment[m_size + 1];
            for (size_t i = 0; i < m_size; i++)
            {
                tmp[i] = data[i];
            }
            tmp[m_size] = val2add;
            delete[] data;
            data = tmp;
            m_size++;
        }
    }
    size_t getSize() const { return m_size; }
    Segment getElementByInd(size_t index /*номер элемента*/) const
    {
        if (m_size <= index)
            //Ошибка !!!
            exit(1);
        else
            return data[index]; // *(data + index)
    }
};

class CircleArray
{
private:
    size_t m_size;
    Circle* data;

public:
    CircleArray()
    {
        m_size = 0;
        data = nullptr;
    }
    ~CircleArray()
    {
        if (data != nullptr)
            delete[] data;
    }
    void addCircle(Circle val2add)
    {
        if (m_size == 0)
        {
            data = new Circle[1];
            data[0] = val2add;
            m_size = 1;
        }
        else
        {
            Circle* tmp = new Circle[m_size + 1];
            for (size_t i = 0; i < m_size; i++)
            {
                tmp[i] = data[i];
            }
            tmp[m_size] = val2add;
            delete[] data;
            data = tmp;
            m_size++;
        }
    }
    size_t getSize() const { return m_size; }
    Circle getElementByInd(size_t index /*номер элемента*/) const
    {
        if (m_size <= index)
            //Ошибка !!!
            exit(1);
        else
            return data[index]; // *(data + index)
    }
};

void outputPoints(const PointArray* array)
{
    for (size_t k = 0; k < array->getSize(); ++k)
    {
        // Output single point
        std::cout << array->getElementByInd(k).x << " " << array->getElementByInd(k).y << std::endl;
    }
}
bool testPointArrayCreation()
{
    PointArray array;
    if (array.getSize() == 0)
        return true;
    return false;
}

bool testPointArraySize()
{
    PointArray array;
    Point p1 = { 1, 2 };
    array.addPoint(p1);
    if (array.getSize() != 1)
        return false;
    return true;
}

bool testPointArrayAccess1()
{
    PointArray array;
    Point p1 = { 1, 2 };
    array.addPoint(p1);
    Point p2 = array.getElementByInd(0);
    if (p1.x == p2.x && p1.y == p2.y)
        return true;
    return false;
}

bool testPointArrayAccessN()
{
    PointArray array;
    Point p1 = { 1, 2 };
    array.addPoint(p1);
    Point p2 = { 2, 2 };
    array.addPoint(p2);
    Point p3 = { 4, 2 };
    array.addPoint(p3);

    Point pp = array.getElementByInd(2);
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
    runAllTests();
    PointArray pointArray;

    Point p1;
    p1.x = 1;
    p1.y = 2;
    pointArray.addPoint(p1);
    Point p2 = { 2, 3 };
    pointArray.addPoint(p2);
    Point p3 = { 5, 3 };
    pointArray.addPoint(p3);
    Point p4 = { 6, 4 };
    pointArray.addPoint(p4);

    cout << "I'm here!\n";
    cout << "CHANGED!\n";
    outputPoints(&pointArray);
    system("pause");
    return 0;
}
