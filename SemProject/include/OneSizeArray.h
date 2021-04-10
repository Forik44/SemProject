#pragma once

template<typename ArrayElement> class OneSizeArray
{
private:
    const size_t m_size;
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
        return m_size;
    };
    class Marker
    {
        marker mark;
    public:
        friend class Array;
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
    OneSizeArray& operator= (const Array& arr)
    {
        for (size_t i = 0; i < arr.getSize(); i++)
        {
            data[i] = arr.data[i];
        }
        size = arr.size;
        return *this;
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
    m_size = size;
    data = nullptr;
};

template<typename ArrayElement> OneSizeArray<ArrayElement>::OneSizeArray(const OneSizeArray<ArrayElement>& original)
{
    size = original.m_size;
    if (size == 0)
        data = nullptr;
    else
    {
        data = new ArrayElement[m_size];
        for (size_t k = 0; k < m_size; ++k)
            data[k] = original.data[k];
    }
};

template<typename ArrayElement> OneSizeArray<ArrayElement>::~OneSizeArray()
{
    if (data != nullptr)
        delete[] data;
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