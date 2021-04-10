#include <iostream>
#include "List.h"
#include "Stack.h"

bool testListAdd(){
    return 1;
}

bool testListIteration(){
    List<int> li;
    li.add(1);
    li.add(2);
    li.add(3);

    List<int>::Marker marker = li.init();
    int k = 1;
    while ( ! (marker == li.afterEnd()) ){
        if ( marker.getElem() != k ) return false;
        ++k;
        ++marker;
    }
    return true;
}

bool testStackSize(){
    Stack<int> sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    if ( sta.getSize() != 3 ) return false;     //было sta.size()
    sta.pop();
    if ( sta.getSize() != 2 ) return false;     //было sta.size()
    sta.pop();
    if ( sta.getSize() != 1 ) return false;     //было sta.size()
    sta.pop();
    if ( sta.getSize() != 0 ) return false;     //было sta.size()
    return true;
}

bool testStackCheck(){
    Stack<int> sta;
    sta.push(1);
    if ( sta.check() != 1 ) return false;
    sta.push(42);
    if ( sta.check() != 42 ) return false;
    sta.push(333);
    if ( sta.check() != 333 ) return false;
    sta.pop();
    if ( sta.check() != 42 ) return false;
    sta.pop();
    if ( sta.check() != 1 ) return false;
    sta.pop();
    try {
        int xfail = sta.check();
        return false;
    }  catch (...) {             //Добавил ...  
    
    }
    return true;
}

bool testStackPopEmpty(){
    Stack<int> sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    sta.pop();
    return true;
}



//#include "Tests.h"
//
//
//bool testPointArrayCreation()
//{
//    PointArray array;
//    if (array.getSize() == 0)
//        return true;
//    return false;
//}
//
//bool testPointArraySize()
//{
//    PointArray array;
//    Point p1 = { 1, 2 };
//    array.addPoint(p1);
//    if (array.getSize() != 1)
//        return false;
//    return true;
//}
//
//bool testPointArrayAccess1()
//{
//    PointArray array;
//    Point p1 = { 1, 2 };
//    array.addPoint(p1);
//    Point p2 = array.getElementByIdx(0);
//    if (p1.x == p2.x && p1.y == p2.y)
//        return true;
//    return false;
//}
//
//bool testPointArrayAccessN()
//{
//    PointList array;
//    Point p1 = { 1, 2 };
//    array.addPoint(p1);
//    Point p2 = { 2, 2 };
//    array.addPoint(p2);
//    Point p3 = { 4, 2 };
//    array.addPoint(p3);
//
//    Point pp = array.getElementByIdx(2);
//    if (pp.x == p3.x && pp.y == p3.y)
//        return true;
//    return false;
//}
//
void runAllTests()
{
//    std::cout << "testPointArrayCreation() " << (testPointArrayCreation() ? "passed" : "failed") << std::endl;
//    std::cout << "testPointArraySize() " << (testPointArraySize() ? "passed" : "failed") << std::endl;
//    std::cout << "testPointArrayAccess1() " << (testPointArrayAccess1() ? "passed" : "failed") << std::endl;
//    std::cout << "testPointArrayAccessN() " << (testPointArrayAccessN() ? "passed" : "failed") << std::endl;
    std::cout << "testListIteration() " << (testListIteration() ? "passed" : "failed") << std::endl;
}

