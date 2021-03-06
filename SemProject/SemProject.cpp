﻿#include "Objects.h"
#include "Array.h"
#include "List.h"
#include "Basicinterface.h"
#include <iostream>

using namespace std;

enum Colors
{
    COL_RED,
    COL_GREEN,
    COL_BLUE
};


/*
void outputPoints(const PointList pointStorage)
{
    for (size_t k = 0; k < pointStorage.getSize(); ++k) {
        cout << "( " << pointStorage.getElementByIdx(k).x << " ; " << pointStorage.getElementByIdx(k).y << " )" << endl;
    }
};
void outputPoints(const PointArray pointStorage)
{
    for (size_t k = 0; k < pointStorage.getSize(); ++k) {
        cout << "( " << pointStorage.getElementByIdx(k).x << " ; " << pointStorage.getElementByIdx(k).y << " )" << endl;
    }
};
void outputPoints(const CircleList circleStorage)
{
    for (size_t k = 0; k < circleStorage.getSize(); ++k) {
        cout << "( " << circleStorage.getElementByIdx(k).center.x << " ; " << circleStorage.getElementByIdx(k).center.y << " ) ";
        cout << "R = " << circleStorage.getElementByIdx(k).r << endl;
    }
};
void outputPoints(const CircleArray circleStorage)
{
    for (size_t k = 0; k < circleStorage.getSize(); ++k) {
        cout << "( " << circleStorage.getElementByIdx(k).center.x << " ; " << circleStorage.getElementByIdx(k).center.y << " ) ";
        cout << "R = " << circleStorage.getElementByIdx(k).r << endl;
    }
};
void outputPoints(const SegmentArray segmentStorage)
{
    for (size_t k = 0; k < segmentStorage.getSize(); ++k) {
        cout << "( " << segmentStorage.getElementByIdx(k).p1.x << " ; " << segmentStorage.getElementByIdx(k).p1.y << " ) :";
        cout << "( " << segmentStorage.getElementByIdx(k).p2.x << " ; " << segmentStorage.getElementByIdx(k).p2.y << " ) " << endl;
    }
};
void outputPoints(const SegmentList segmentStorage)
{
    for (size_t k = 0; k < segmentStorage.getSize(); ++k) {
        cout << "( " << segmentStorage.getElementByIdx(k).p1.x << " ; " << segmentStorage.getElementByIdx(k).p1.y << " ) :";
        cout << "( " << segmentStorage.getElementByIdx(k).p2.x << " ; " << segmentStorage.getElementByIdx(k).p2.y << " ) " << endl;
    }
};
*/

//void OutputPoints(const Array<Point> pointStorage)
//{
//    for (size_t k = 0; k < pointStorage.getSize(); ++k) {
//        cout << "( " << pointStorage.getElementByIdx(k).x << " ; " << pointStorage.getElementByIdx(k).y << " )" << endl;
//    }
//}

int main(int argc, char* argv[])
{
    try {
        BasicInterface bi();

        while (true) {
            char v = std::cin.get();
            switch (v) {
            case 'a': {// добавить объект

                break;
            }
            case 'l': {// показать идентификаторы объектов

                break;
            }
            case 'd': { // " отобразить " состояниие рисунка
            }

            case 'r': {// добавить требование

                break;
            }
            case 'x': // выйти из программы
            }
        }
    }
    catch (...) {
        std::cout << "Achtung!!!" << std::endl;
    }


    system("pause");
    return 0;
}
