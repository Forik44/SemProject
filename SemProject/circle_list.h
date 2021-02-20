#pragma once

#include "objects.h"

class CircleList {
private:
    struct Node
    {
        Node* next;
        Circle data;
        int idx;
    };
    size_t size;
    Node* first, * last;

public:
    CircleList();    //constructor
    CircleList(const CircleList& original);
    ~CircleList();   //destructor
    void addCircle(Circle val2add);
    Circle getElementByIdx(size_t Num) const;
    size_t getSize() const;
}; 
