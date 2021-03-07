#pragma once

#include <cstdlib>

template<typename ArrayElement> class Array{
private:
    size_t size;
    ArrayElement* data;
    struct marker{
        ArrayElement* Elem;
        size_t Idx;
        size_t markerSize;
    };
public:
    Array();  
    Array(const Array& original);
    ~Array();   
    void add(ArrayElement val2add);
    ArrayElement getElementByIdx(size_t idx);
    bool removeElementByIdx(size_t idx);
   /* removeByMarker(const Marker&);*/
    size_t getSize() const
    {
        return size;
    };
    class Marker
    {
        marker mark;
    public:
        friend class Array;
        ArrayElement& getElem()
        {
            return *mark.Elem;
        };
        const ArrayElement& getElem() const
        {
            return *mark.Elem;
        };
        void moveNext()
        {
            mark.Elem += 1;
            mark.Idx += 1;
        };
        bool canMoveNext()
        {
            if (mark.Idx < mark.markerSize)
                return true;
            else
                return false;
        };
        void setMarkerSize(size_t size)
        {
            mark.markerSize = size;
        }
    };
    Marker init()
    {
        Marker ma;
        ma.setMarkerSize(size);
        ma.mark.Elem = data;
        ma.mark.Idx = 0;
        return ma;
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

template<typename ArrayElement> ArrayElement Array<ArrayElement>::getElementByIdx(size_t idx)
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





