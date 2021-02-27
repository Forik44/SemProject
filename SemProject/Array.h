#ifndef ARRAY_H
#define ARRAY_H
#include <cstdlib>

template<typename ArrayElement> class Array {
private:
    size_t size;
    ArrayElement* data;
public:
    Array();  //constructor
    Array(const Array& original);
    ~Array();   //destructor
    void add(ArrayElement val2add);
    ArrayElement getElementByIdx(size_t idx) const;
    size_t getSize() const
    {
        return size;
    };
};

template<typename ArrayElement> Array<ArrayElement>::Array()
{
    size = 0;
    data = nullptr;
};
template<typename ArrayElement> Array<ArrayElement>::Array(const Array<ArrayElement>& original)
{
    size = original.size;
    if (size == 0)
        data = nullptr;
    else
    {
        data = new ArrayElement[size];
        for (size_t k = 0; k < size; ++k)
            data[k] = original.data[k];
    }
}
template<typename ArrayElement> Array<ArrayElement>::~Array()
{
    if (data != nullptr)
        delete[] data;
};
template<typename ArrayElement> void Array<ArrayElement>::add(ArrayElement val2add)
{
    if (size == 0)
    {
        data = new ArrayElement[1];
        data[0] = val2add;
        size = 1;
    }
    else
    {
        ArrayElement* tmp = new ArrayElement[size + 1];
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
template<typename ArrayElement> ArrayElement Array<ArrayElement>::getElementByIdx(size_t idx /*����� ��������*/) const
{
    if (size <= idx)
        //������ !!!
        exit(1);
    else
        return data[idx]; // *(data + index)
};





#endif // ARRAY_H
