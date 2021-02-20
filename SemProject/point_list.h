#pragma once

#include "Objects.h"

class PointList {
private:
    struct Node
    {
        Node* next;
        Point data;
        int idx;
    };
    size_t size;
    Node* first, * last;

public:
    PointList();    //constructor
    ~PointList();   //destructor
    void addPoint(Point val2add);
    Point getElementByInd(size_t Num) const;
    size_t getSize() const;
};