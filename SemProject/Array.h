#pragma once

#include <cstdlib>

template<typename ArrayElement> class Array{
private:
    size_t size;
    ArrayElement* data;
public:
    Array();  //constructor
    Array(const Array& original);
    ~Array();   //destructor
    void add(ArrayElement val2add);
    ArrayElement getElementByIdx(size_t idx) const;
    bool removeByIdx(size_t idx);
    size_t getSize() const
    {
        return size;
    };
};



