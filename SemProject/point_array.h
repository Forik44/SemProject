#pragma once

#include "objects.h"

class PointArray {
private:
    size_t size;
    Point* data;
public:
    PointArray();  //constructor
    PointArray(const PointArray& original);
    ~PointArray();   //destructor
    void addPoint(Point val2add);
    Point getElementByIdx(size_t idx) const;
    size_t getSize() const;

};

