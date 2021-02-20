
#include "circle_array.h"


CircleArray::CircleArray()
{
    size = 0;
    data = nullptr;
};
CircleArray::CircleArray(const CircleArray& original)
{
    size = original.size;
    if (size == 0)
        data = nullptr;
    else
    {
        data = new Circle[size];
        for (size_t k = 0; k < size; ++k)
            data[k] = original.data[k];
    }
}
CircleArray::~CircleArray()
{
    if (data != nullptr)
        delete[] data;
};
void CircleArray::addCircle(Circle val2add)
{
    if (size == 0)
    {
        data = new Circle[1];
        data[0] = val2add;
        size = 1;
    }
    else
    {
        Circle* tmp = new Circle[size + 1];
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
Circle CircleArray::getElementByIdx(size_t idx /*номер элемента*/) const
{
    if (size <= idx)
        //Ошибка !!!
        exit(1);
    else
        return data[idx]; // *(data + index)
};
