#pragma once

#include <cstdlib>
#include <iostream>

template<typename ArrayElement> class Array{
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
    Array();  
    Array(const Array& original);
    Array(Array&& original);
    ~Array();   
    void add(ArrayElement val2add);
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
    Array& operator= (const Array& arr)
    {
        Array tmp = new Array[size];
        for (size_t i = 0; i < size; i++)
        {
            tmp[i] = arr[i];
        }
        delete[] *this;
        return tmp;
    }
    Array& operator= (Array&& arr)
    {
        delete[] data;
        data = arr.data;
        size = arr.size;
        arr.data = nullptr;
        arr.size = 0;
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
    Marker initAfterAddingNewElement()
    {
        Marker ma;
        ma.setMarkerSize(size);
        ma.mark.Elem = data + size - 2;
        ma.mark.Idx = size - 2;
        return ma;
    };
    friend class Marker;
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
template<typename ArrayElement> Array<ArrayElement>::Array(Array<ArrayElement>&& original)
{
    data = original.data;
    size = original.size;
    original.data = nullptr;
    original.size = 0;
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
template<typename ArrayElement> ArrayElement& Array<ArrayElement>::operator[](size_t idx)
{
    if (size <= idx)
        exit(1);
    else
        return data[idx]; // *(data + index)
};
template<typename ArrayElement> const ArrayElement& Array<ArrayElement>::operator[](size_t idx)const
{
    if (size <= idx)
        exit(1);
    else
        return data[idx]; // *(data + index)
};
template<typename ArrayElement> bool Array<ArrayElement>::removeElementByIdx(size_t idx)
{
    if ((size <= idx) || (idx < 0))
        return false;
    else if (size == 1)
    {
        delete[] data;
        data = nullptr;
        size--;
        return true;
    }
    else
    {
        ArrayElement* tmp = new ArrayElement[size - 1];

        int k = 0;
        for (size_t i = 0; i < size; i++)
        {
            if (idx != i)
            {
                tmp[k] = data[i];
                k++;
            }

        };      

        delete[] data;
        data = tmp;
        size--;
        return true;
    }
};


template<> class Array<bool> {
private:
    size_t size;
    size_t byte_size;
    unsigned char* data;
   
public:
    Array()
    {
        size = byte_size = 0;
        data = nullptr;
    };
    Array(const Array& original)
    {
        delete[] data;
        data = new unsigned char[original.byte_size];
        for (int i = 0; i < original.byte_size; i++)
        {
            data[i] = original[i];
        }
    };
    ~Array()
    {
        size = byte_size = 0;
        delete[] data;
    };
    void add(bool val2add)
    {
        if (size % (sizeof(unsigned char) * 8) == 0)
        {
            unsigned char* tmp = new unsigned char[byte_size + 1];

            for (int i = 0; i < byte_size; i++)
            {
                tmp[i] = data[i];
            }
            delete[] data;
            data = tmp;
            byte_size++;
            data[byte_size - 1] = 0;
        }

        unsigned char mask = 1; 
        int shift = size % (sizeof(unsigned char) * 8);
        mask = mask << shift;
      
        if (val2add)
            data[byte_size - 1] = data[byte_size - 1] | mask;
        else
            data[byte_size - 1] = data[byte_size - 1] & (~mask);

        size++;
    };

    bool operator[](size_t idx)
    {
        unsigned char mask = 1;
        int shift = idx % (sizeof(unsigned char) * 8);
        mask = mask << shift;
        int byte_idx = idx / (sizeof(unsigned char) * 8);
        return (data[byte_idx] & mask);
    };
    const bool operator[](size_t idx)const
    {
        unsigned char mask = 1;
        mask = mask << idx % (sizeof(unsigned char) * 8);
        return (data[byte_size - 1] & mask);
    };
    bool removeElementByIdx(size_t idx)
    {
        if ((size <= idx) || (idx < 0))
            return false;
        else if (size == 1)
        {
            delete[] data;
            data = nullptr;
            size--;
            return true;
        }
        else
        {
            bool* tmp;
            if (size - 1 % sizeof(bool) == 0)
            {
                byte_size--;
                tmp = new bool[byte_size - 1];
            }
            else
            {
                tmp = new bool[byte_size];
            }

         
          
        }
    };
    size_t getSize() const
    {
        return size;
    };
    
    Array& operator= (const Array& arr)
    {
        delete[] data;
        data = new unsigned char[arr.byte_size];
        for (int i = 0; i < arr.byte_size; i++)
        {
            data[i] = arr[i];
        }
        return *this;
    }
   
    
};



