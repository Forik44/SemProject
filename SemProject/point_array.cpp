
#include "point_array.h"


PointArray::PointArray()    //constructor
{
    size = 0;
    data = nullptr;
}
PointArray::PointArray(const PointArray& original)
{
    size = original.size;
    if (size == 0)
        data = nullptr;
    else
    {
        data = new Point[size];
        for (size_t k = 0; k < size; ++k)
            data[k] = original.data[k];
    }
}
PointArray::~PointArray()   //destructor
{
    if (data != nullptr)
        delete[] data;
};
void PointArray::addPoint(Point val2add)
{
    if (size == 0) {
        data = new Point[1];
        data[0] = val2add;
        size = 1;
    }
    else {
        Point* tmp = new Point[size + 1];
        for (size_t i = 0; i < size; i++)
            tmp[i] = data[i];
        tmp[size] = val2add;
        delete[] data;
        data = tmp;
        size++;
    }
};
Point PointArray::getElementByIdx(size_t idx) const
{
    if (idx < size)
        return data[idx];
    else
        exit(1); //Error
};


