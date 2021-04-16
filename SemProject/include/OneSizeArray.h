#pragma once

template<typename ArrayElement> class OneSizeArray
{
private:
    size_t size;
    ArrayElement* data;
    struct marker
    {
        ArrayElement* Elem;
        size_t Idx;
        size_t markerSize;
    };
public:
    OneSizeArray(size_t size);
    OneSizeArray(const OneSizeArray& original);
    ~OneSizeArray();
    ArrayElement& operator[](size_t idx);
    const ArrayElement& operator[](size_t idx)const;
    bool removeElementByIdx(size_t idx);
    size_t getSize() const
    {
        return size;
    };
    class Marker
    {
        marker mark;
    public:
        friend OneSizeArray;
        ArrayElement& operator*()
        {
            return *mark.Elem;
        };
        const ArrayElement& operator*() const
        {
            return *mark.Elem;
        };
        void operator++()
        {
            mark.Elem++;
            mark.Idx++;
        };
        void operator++(int)
        {
            mark.Elem++;
            mark.Idx++;
        };
        bool operator==(const Marker& secondMarker) const
        {
            return (this->mark.Elem == secondMarker.mark.Elem && this->mark.Idx == secondMarker.mark.Idx);
        };
        bool operator!=(const Marker& secondMarker) const
        {
            return !(*this == secondMarker);
        }
        bool canMoveNext()
        {
            return (mark.Idx < mark.markerSize);
        };
        void setMarkerSize(size_t size)
        {
            mark.markerSize = size;
        }
    };
    OneSizeArray& operator= (const OneSizeArray& arr)
    {
        if (this->getSize() != arr.getSize())
        {
           throw -1;
        }
        for (size_t i = 0; i < arr.getSize(); i++)
        {
            data[i] = arr.data[i];
        }
        return *this;
    }
    friend OneSizeArray operator*(const double coefficient , const OneSizeArray& arr)
    {
        OneSizeArray<ArrayElement> tmp(arr.getSize());
        for (size_t i = 0; i < arr.getSize(); i++)
        {
            tmp[i] = coefficient * arr[i];
        }
        return tmp;
    }
    friend OneSizeArray operator+(const OneSizeArray& arr1, const OneSizeArray& arr2)
    {
        if (arr1.getSize() != arr2.getSize())
        {
            throw -1;
        }
        OneSizeArray<ArrayElement> tmp1(arr1.getSize());
        for (size_t i = 0; i < arr1.getSize(); i++)
        {
            tmp1[i] = arr1[i] + arr2[i];
        }
        return tmp1;
    }
    void setElementByIdx(size_t idx, ArrayElement val2add)
    {
        if (idx >= size)
            throw -1;
        data[idx] = val2add;
    }
    Marker init()
    {
        Marker ma;
        ma.setMarkerSize(size);
        ma.mark.Elem = data;
        ma.mark.Idx = 0;
        return ma;
    };
    Marker afterEnd()
    {
        Marker ma;
        ma.setMarkerSize(size);
        ma.mark.Elem = data + size;
        ma.mark.Idx = ma.mark.markerSize;
        return ma;
    };
    friend class Marker;
};

template<typename ArrayElement> OneSizeArray<ArrayElement>::OneSizeArray(size_t size)
{
    this->size = size;
    data = new ArrayElement(size);
    for (size_t i = 0; i < size; i++)
    {
        data[i] = 0;
    }
};

template<typename ArrayElement> OneSizeArray<ArrayElement>::OneSizeArray(const OneSizeArray<ArrayElement>& original)
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

template<typename ArrayElement> OneSizeArray<ArrayElement>::~OneSizeArray()
{
   /* if (data != nullptr)
        delete data;*/
   
};

template<typename ArrayElement> ArrayElement& OneSizeArray<ArrayElement>::operator[](size_t idx)
{
    if (size <= idx)
        exit(1);
    else
        return data[idx]; // *(data + index)
};
template<typename ArrayElement> const ArrayElement& OneSizeArray<ArrayElement>::operator[](size_t idx)const
{
    if (size <= idx)
        exit(1);
    else
        return data[idx]; // *(data + index)
};
template<typename ArrayElement> bool OneSizeArray<ArrayElement>::removeElementByIdx(size_t idx)
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
        return isFound;
    }
};
