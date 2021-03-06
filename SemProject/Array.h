#pragma once

#include <cstdlib>

template<typename ArrayElement> class Array{
private:
    size_t size;
    ArrayElement* data;
    struct marker{
        ArrayElement Elem;
        size_t Idx;
    };
    marker mark;
public:
    Array();  
    Array(const Array& original);
    ~Array();   
    void add(ArrayElement val2add);
    ArrayElement getElementByIdx(size_t idx) const;
    bool removeElementByIdx(size_t idx);
    size_t getSize() const
    {
        return size;
    };
    void unit();
    ArrayElement getElem()const;
    void moveNext();
    bool canMoveNext();
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
};

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

template<typename ArrayElement> ArrayElement Array<ArrayElement>::getElementByIdx(size_t idx) const
{
    if (size <= idx)
        exit(1);
    else
        return data[idx]; // *(data + index)
};

template<typename ArrayElement> bool Array<ArrayElement>::removeElementByIdx(size_t idx)
{
    if (size <= idx)
        return 0;
    else
    {
        bool isFound = false;
        ArrayElement* tmp = new ArrayElement[size - 1];
        for (size_t i = 0; i < size; i++)
        {
            if (idx == i)
                isFound = true;
            if (!isFound)
                tmp[i] = data[i];
            else
            {
                tmp[i] = data[i + 1];
            }
        };
        delete[] data;
        data = tmp;
        size--;
    }
};

template<typename ArrayElement> void Array<ArrayElement>::unit()
{
    mark.Elem = getElementByIdx(0);
    mark.Idx = 0;
};

template<typename ArrayElement> ArrayElement Array<ArrayElement>::getElem()const
{
    return mark.Elem;
};

template<typename ArrayElement> void Array<ArrayElement>::moveNext()
{
    mark.Elem = getElementByIdx(mark.Idx + 1);
    mark.Idx += 1;
};

template<typename ArrayElement> bool Array<ArrayElement>::canMoveNext()
{
    if (mark.Idx < size)
        return true;
    else
        return false;
};


