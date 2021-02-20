#pragma once

#include "objects.h"

class CircleArray {
private:
    size_t size;
    Circle* data;
public:
    CircleArray();
    CircleArray(const CircleArray& original);
    ~CircleArray();
    void addCircle(Circle val2add);
    size_t getSize() const { return size; };
    Circle getElementByIdx(size_t index /*номер элемента*/) const;
};