#pragma once

#include "objects.h"

class SegmentList {
private:
    struct Node
    {
        Node* next;
        Segment data;
        size_t idx;
    };
    size_t size;
    Node* first, * last;

public:
    SegmentList();    //constructor
    SegmentList(const SegmentList& original);
    ~SegmentList();   //destructor
    void addSegment(Segment val2add);
    Segment getElementByIdx(size_t Num) const;
    size_t getSize() const;
};
