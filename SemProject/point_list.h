#pragma once
#include <iostream>
#include <cstddef>
#include "objects.h"

using namespace std;
class PointList {
private:
	size_t size;
	Point data;
	PointList* next;
	
public:
	PointList();
	~PointList();
	void addPoint(Point val2add);
	size_t getSize() const;
	Point getElementByInd(size_t index /*номер элемента*/) const;
};



