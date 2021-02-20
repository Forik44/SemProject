#pragma once

#include "objects.h"
#include "point_list.h"
#include "point_array.h"
#include <iostream>


bool testPointArrayCreation()
{
    PointArray array;
    if (array.getSize() == 0)
        return true;
    return false;
}

bool testPointArraySize()
{
    PointArray array;
    Point p1 = { 1, 2 };
    array.addPoint(p1);
    if (array.getSize() != 1)
        return false;
    return true;
}

bool testPointArrayAccess1()
{
    PointArray array;
    Point p1 = { 1, 2 };
    array.addPoint(p1);
    Point p2 = array.getElementByInd(0);
    if (p1.x == p2.x && p1.y == p2.y)
        return true;
    return false;
}

bool testPointArrayAccessN()
{
    PointList array;
    Point p1 = { 1, 2 };
    array.addPoint(p1);
    Point p2 = { 2, 2 };
    array.addPoint(p2);
    Point p3 = { 4, 2 };
    array.addPoint(p3);

    Point pp = array.getElementByInd(2);
    if (pp.x == p3.x && pp.y == p3.y)
        return true;
    return false;
}

void runAllTests()
{
    std::cout << "testPointArrayCreation() " << (testPointArrayCreation() ? "passed" : "failed") << std::endl;
    std::cout << "testPointArraySize() " << (testPointArraySize() ? "passed" : "failed") << std::endl;
    std::cout << "testPointArrayAccess1() " << (testPointArrayAccess1() ? "passed" : "failed") << std::endl;
    std::cout << "testPointArrayAccessN() " << (testPointArrayAccessN() ? "passed" : "failed") << std::endl;
}