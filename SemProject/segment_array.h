#pragma once

#include "objects.h"

class SegmentArray {
private:
    size_t size;
    Segment* data;
public:
    SegmentArray();  //constructor
    SegmentArray(const SegmentArray& original);
    ~SegmentArray();   //destructor
    void addSegment(Segment val2add);
    Segment getElementByIdx(size_t idx) const;
    size_t getSize() const
    {
        return size;
    };
};

