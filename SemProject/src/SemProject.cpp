﻿#include "TreeDict.h"
#include "basicinterface.h"
#include "PSDrawer.h"
#include <iostream>
#include <locale>
#include "Stack.h"

using namespace std;

enum Colors
{
    COL_RED,
    COL_GREEN,
    COL_BLUE
};

std::ostream& operator<<(std::ostream& ost, const Point& p)
{
    ost << '(' << p.x << ',' << p.y << ')';
    return ost;
}

std::ostream& operator<<(std::ostream& ost, enum ParamType& p)
{
    string ParamTypesNames[] { 
        "PT_ERROR",
        "PT_POINT",
        "PT_CIRCLE",
        "PT_SEGMENT",
        "PT_CX",
        "PT_CY",
        "PT_R",
        "PT_P1X",
        "PT_P2X",
        "PT_P1Y",
        "PT_P2Y",
        "PT_PX",
        "PT_PY" };
    cout << ParamTypesNames[p];
    return ost;
}

std::ostream& operator<<(std::ostream& ost, enum ObjType& obj)
{
    string ObjTypesNames[] {
    "OT_ERROR",
    "OT_POINT",
    "OT_SEGMENT",
    "OT_CIRCLE"
    };
    cout << ObjTypesNames[obj];
    return ost;
}

//
//Point p1, p2;
//std::cout << p1 << "   " << p2 << std::endl;
//
//operator<<(operator<<(operator<<(operator<<(std::cout, p1), "    "), p2), std::endl);*/
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
//void OutputPoints(Array<Point>& pointStorage)
//{
//    Array<Point>::Marker m = pointStorage.init();
//    //Константный маркер
//    while (m != pointStorage.afterEnd())
//    {
//        cout << *m << endl;
//        ++m;
//    }
//}
//int main(int argc, char* argv[])
//{
//    setlocale(LC_ALL, "Russian");
//    BasicInterface bi;
//    try {
//        while (false) {
//            cout << "Что вы хотите сделать?\n";
//            cout << "Добавить объект(a)\nПоказать идентификаторы объектов(l)\nОтобразить состояниие рисунка(d)\nДобавить требование(r)\nВыйти из программы(x)\n";
//            char startLetter = cin.get();
//            system("cls");
//            switch (startLetter) {
//            case 'a': {// добавить объект
//                char obj = cin.get();
//                cout << "Какое тип объекта вы хотите добавить?" << endl;
//                cout << "Точка (p)\nОтрезок (s)\nКруг (с)\n";
//                obj = cin.get();
//                if (obj == 'p')
//                {
//                    int x, y;
//                    cout << "Введите координаты точки:" << endl;
//                    cout << "x: ";
//                    cin >> x;
//                    cout << "y: ";
//                    cin >> y;
//                    //Добавляем точку p1
//
//                }
//                else if (obj == 's')
//                {
//                    int x1, x2, y1, y2;
//                    cout << "Введите координаты 2-ух точек:" << endl;
//                    cout << "Первая точка:" << endl;
//                    cout << "x: ";
//                    cin >> x1;
//                    cout << "y: ";
//                    cin >> y1;
//                    cout << "Вторая точка:" << endl;
//                    cout << "x: ";
//                    cin >> x2;
//                    cout << "y: ";
//                    cin >> y2;
//                    //Добавляем p1 и p2
//                    //Добавляем сегмент
//                }
//                else if (obj == 'c')
//                {
//                    int R, x, y;
//                    cout << "Введите координаты центра: " << endl;
//                    cout << "x: ";
//                    cin >> x;
//                    cout << "y: ";
//                    cin >> y;
//                    cout << "Введите радиус окружности: " << endl;
//                    cout << "R: ";
//                    cin >> R;
//                    //Добавляем точку P
//                    //Добавляем окружность с центром в точке P радиуса R
//                }
//                else
//                    cout << "Unknown command" << endl;
//                break;
//            }
//            case 'l': {// показать идентификаторы объектов
//                
//                break;
//            }
//            case 'd': { // " отобразить " состояниие рисунка
//            }
//
//            case 'r': {// добавить требование
//                char rq;
//                cout << "Какое требование вы хотите добавить?" << endl;
//                cout << "Параллельность (p)\nОртогональность (о)\nЗафиксировать расстояние между объектами (d)\nГруппировка (g)\nСовмещение (c)\n";
//                cin >> rq;
//                if (rq == 'p')
//                {
//                    size_t ID1, ID2;
//                    cout << "Введите идентификаторы двух прямых:" << endl;
//                    cout << "Первая прямая: ";
//                    cin >> ID1;
//                    //Проверка что заданный ID принадлежит прямой 
//                    cout << "Вторая прямая: ";
//                    cin >> ID2;
//                    //Проверка что заданный ID принадлежит прямой 
//                    //Добавление свойства
//                }
//                else if (rq == 'o')
//                {
//                    size_t ID1, ID2;
//                    cout << "Введите идентификаторы двух прямых:" << endl;
//                    cout << "Первая прямая: ";
//                    cin >> ID1;
//                    //Проверка что заданный ID принадлежит прямой 
//                    cout << "Вторая прямая: ";
//                    cin >> ID2;
//                    //Проверка что заданный ID принадлежит прямой 
//                    //Добавление свойства
//                }
//                else if (rq == 'd')
//                {
//                    size_t ID1, ID2;
//                    cout << "Введите идентификаторы двух объъектов:" << endl;
//                    cout << "Первая объект: ";
//                    cin >> ID1;
//                    //Проверка что заданный ID принадлежит какому-то объекту 
//                    cout << "Второй объект: ";
//                    cin >> ID2;
//                    //Проверка что заданный ID принадлежит какому-то объекту
//                    //Добавление свойства
//                }
//                else if (rq == 'g')
//                {
//                    size_t amount;
//                    cout << "Введите количество объектов:";
//                    cin >> amount;
//                    size_t* IDs = new size_t[amount];
//                    for (size_t i = 0; i < amount; i++)
//                    {
//                        cout << "Введите " << i + 1 << " объект: ";
//                        cin >> IDs[i];
//                    }
//                }
//                else if (rq == 'c')
//                {
//
//                }
//                else
//                    cout << "Unknown command" << endl;
//                break;
//            }
//            case 'x': // выйти из программы 
//            {
//                break;
//            }
//            }
//        }
//    }
//    catch (...) {
//        std::cout << "Achtung!!!" << std::endl;
//    }
//   
// 
//    bi.addObject(OT_SEGMENT);
//    bi.addObject(OT_POINT);
//    bi.addObject(OT_POINT);
//    ID id;
//    id.setID(1);
//
//    UniDict<ParamType, double> objProperties = bi.queryObjProperties(id);
//
//    for (UniDict<ParamType, double>::Marker mark = objProperties.init(); mark != objProperties.afterEnd(); mark++)
//    {
//        cout << (*mark).key << " : " << (*mark).val << endl;
//    }
//  
//   
//    return 0;
//}

int main()
{
    /*try {
        PSDrawer test("test.ps");
        test.drawLine(100.0, 20.0, 100.0, 400.0);
        test.drawPoint(200.0, 200.0);
        test.drawCircle(200.0, 200.0, 100.0);
    }  catch (errors& A) {
        std::cout << A.message;
    }*/


    BasicInterface bi;

    Array<ID> arr;
    
    ID id1, id2, id3;

    id1 = bi.addObject(OT_SEGMENT);
    id2 = bi.addObject(OT_SEGMENT);
    id3 = bi.addObject(OT_SEGMENT);

    arr.add(id1);
    arr.add(id2);
    arr.add(id3);

    bi.addRequirement(arr, RT_PARALLEL);

  
    bi.solveComplexReq();


    for (int i = 0; i < arr.getSize(); i++)
    {
        UniDict<ParamType, double> obj = bi.queryObjProperties(arr[i]);

        for (UniDict<ParamType, double> ::Marker m = obj.init(); m != obj.afterEnd(); m++)
        {
            ParamType pt = (*m).key;
            cout << pt << " " << (*m).val << endl;
        }

    }

    

   

  
   


    return 0;
};