#pragma once
#include <iostream>
#include <cstddef>
#include "objects.h"

using namespace std;
class PointList
{
private:
	struct Node
	{
		Node* next;
		Point* data;
		int idx;
	};
	size_t size;
	Node* first, * last;
public:
	PointList();
	~PointList();
	void addPoint(Point& val2add);
	size_t getSize() const;
	Point getElementByInd(size_t index /*номер элемента*/) const;
};



