#include "segment_array.h"

SegmentArray::SegmentArray()
{
    size = 0;
    data = nullptr;
};
SegmentArray::SegmentArray(const SegmentArray& original)
{
    size = original.size;
    if (size == 0)
        data = nullptr;
    else
    {
        data = new Segment[size];
        for (size_t k = 0; k < size; ++k)
            data[k] = original.data[k];
    }
}
SegmentArray::~SegmentArray()
{
    if (data != nullptr)
        delete[] data;
};
void SegmentArray::addSegment(Segment val2add)
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
};
Segment SegmentArray::getElementByIdx(size_t idx /*номер элемента*/) const
{
    if (size <= idx)
        //Ошибка !!!
        exit(1);
    else
        return data[idx]; // *(data + index)
};
