

#include <iostream>
#include <cstddef>
#include "objects.h"

using namespace std;
class PointArray {
private:
	size_t m_size;
	Point* data;
public:
	PointArray();
	PointArray(const PointArray& original);
	~PointArray();
	void addPoint(Point val2add);
	size_t getSize() const;
	Point getElementByInd(size_t index /*номер элемента*/) const;
};




