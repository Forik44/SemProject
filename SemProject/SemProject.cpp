
#include "Basicinterface.h"
#include <iostream>
#include <locale>

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
    setlocale(LC_ALL, "Russian");
    BasicInterface bi;
    try {
        while (true) {
            cout << "Что вы хотите сделать?\n";
            cout << "Добавить объект(a)\nПоказать идентификаторы объектов(l)\nОтобразить состояниие рисунка(d)\nДобавить требование(r)\nВыйти из программы(x)\n";
            char startLetter = cin.get();
            system("cls");
            switch (startLetter) {
            case 'a': {// добавить объект
                char obj = cin.get();
                cout << "Какое тип объекта вы хотите добавить?" << endl;
                cout << "Точка (p)\nОтрезок (s)\nКруг (с)\n";
                obj = cin.get();
                if (obj == 'p')
                {
                    int x, y;
                    cout << "Введите координаты точки:" << endl;
                    cout << "x: ";
                    cin >> x;
                    cout << "y: ";
                    cin >> y;
                    //Добавляем точку p1

                }
                else if (obj == 's')
                {
                    int x1, x2, y1, y2;
                    cout << "Введите координаты 2-ух точек:" << endl;
                    cout << "Первая точка:" << endl;
                    cout << "x: ";
                    cin >> x1;
                    cout << "y: ";
                    cin >> y1;
                    cout << "Вторая точка:" << endl;
                    cout << "x: ";
                    cin >> x2;
                    cout << "y: ";
                    cin >> y2;
                    //Добавляем p1 и p2
                    //Добавляем сегмент
                }
                else if (obj == 'c')
                {
                    int R, x, y;
                    cout << "Введите координаты центра: " << endl;
                    cout << "x: ";
                    cin >> x;
                    cout << "y: ";
                    cin >> y;
                    cout << "Введите радиус окружности: " << endl;
                    cout << "R: ";
                    cin >> R;
                    //Добавляем точку P
                    //Добавляем окружность с центром в точке P радиуса R
                }
                else
                    cout << "Unknown command" << endl;
                break;
            }
            case 'l': {// показать идентификаторы объектов
                
                break;
            }
            case 'd': { // " отобразить " состояниие рисунка
            }

            case 'r': {// добавить требование
                char rq;
                cout << "Какое требование вы хотите добавить?" << endl;
                cout << "Параллельность (p)\nОртогональность (о)\nЗафиксировать расстояние между объектами (d)\nГруппировка (g)\nСовмещение (c)\n";
                cin >> rq;
                if (rq == 'p')
                {
                    size_t ID1, ID2;
                    cout << "Введите идентификаторы двух прямых:" << endl;
                    cout << "Первая прямая: ";
                    cin >> ID1;
                    //Проверка что заданный ID принадлежит прямой 
                    cout << "Вторая прямая: ";
                    cin >> ID2;
                    //Проверка что заданный ID принадлежит прямой 
                    //Добавление свойства
                }
                else if (rq == 'o')
                {
                    size_t ID1, ID2;
                    cout << "Введите идентификаторы двух прямых:" << endl;
                    cout << "Первая прямая: ";
                    cin >> ID1;
                    //Проверка что заданный ID принадлежит прямой 
                    cout << "Вторая прямая: ";
                    cin >> ID2;
                    //Проверка что заданный ID принадлежит прямой 
                    //Добавление свойства
                }
                else if (rq == 'd')
                {
                    size_t ID1, ID2;
                    cout << "Введите идентификаторы двух объъектов:" << endl;
                    cout << "Первая объект: ";
                    cin >> ID1;
                    //Проверка что заданный ID принадлежит какому-то объекту 
                    cout << "Второй объект: ";
                    cin >> ID2;
                    //Проверка что заданный ID принадлежит какому-то объекту
                    //Добавление свойства
                }
                else if (rq == 'g')
                {
                    size_t amount;
                    cout << "Введите количество объектов:";
                    cin >> amount;
                    size_t* IDs = new size_t[amount];
                    for (size_t i = 0; i < amount; i++)
                    {
                        cout << "Введите " << i + 1 << " объект: ";
                        cin >> IDs[i];
                    }
                }
                else if (rq == 'c')
                {

                }
                else
                    cout << "Unknown command" << endl;
                break;
            }
            case 'x': // выйти из программы 
            {
                break;
            }
            }
        }
    }
    catch (...) {
        std::cout << "Achtung!!!" << std::endl;
    }
   
 
    bi.addObject(OT_POINT);
    bi.addObject(OT_POINT);
    bi.addObject(OT_POINT);
 
  /*
    Array<int> pointArray;

    pointArray.add(5);
    pointArray.add(7);
    pointArray.add(13);
    pointArray.add(15);
    
   
    Array<int>::Marker marker = pointArray.init();
    while (marker.canMoveNext())
    {
        cout << marker.getElem() << " ";
        marker.moveNext();
        cout << identificator << " ";
    };
   pointArray.add(16);
   marker = pointArray.initAfterAddingNewElement();
   while (marker.canMoveNext())
   {
       cout << marker.getElem() << " ";
       marker.moveNext();
   };
    */
    system("pause");
    return 0;
}
