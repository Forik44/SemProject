
#include <iostream>
#include "objects.h"
#include "point_array.h"
using namespace std;

    PointArray::PointArray()
    {
        m_size = 0;
        data = nullptr;
    }
    PointArray::PointArray(const PointArray& original)
    {
        m_size = original.m_size;
        if (m_size == 0)
            data = nullptr;
        else
        {
            data = new Point[m_size];
            for (size_t i = 0; i < m_size; i++)
            {
                data[i] = original.data[i];
            }
        }
    }
    PointArray::~PointArray()
    {
        if (data != nullptr)
            delete[] data;
    }
    void PointArray::addPoint(Point val2add)
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
    size_t PointArray::getSize() const { return m_size; }
    Point PointArray::getElementByInd(size_t index /*номер элемента*/) const
    {
        if (m_size <= index)
            //Ошибка !!!
            exit(1);
        else
            return data[index]; // *(data + index)
    }




