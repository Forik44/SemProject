#include"point_array.h"
#include"point_list.h"
#include "Tests.cpp"
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

void outputPoints(const PointArray array)
{
    for (size_t k = 0; k < array.getSize(); ++k)
    {
        // Output single point
        std::cout << array.getElementByInd(k).x << " " << array.getElementByInd(k).y << std::endl;
    }
}
void outputPoints(const PointList array)
{
    for (size_t k = 0; k < array.getSize(); ++k)
    {
        // Output single point
        std::cout << array.getElementByInd(k).x << " " << array.getElementByInd(k).y << std::endl;
    }
}

int main(int argc, char* argv[])
{
    runAllTests();
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

    
    outputPoints(pointStorage);
    outputPoints(pointStorage);
    system("pause");
    return 0;
}
