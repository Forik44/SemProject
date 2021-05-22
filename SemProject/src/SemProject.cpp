#include "TreeDict.h"
#include "basicinterface.h"
#include "PSDrawer.h"
#include <iostream>
#include <locale>
#include "Stack.h"
#include "Array.h"
#include "OneSizeArray.h"


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
            case 'd': { // " отобразить " состояниие рисунка

                Array<ID> ids = bi.ReceiveIdObjects();
                PSDrawer ps("picture",10);

                for (Array<ID>::Marker mark = ids.init(); mark != ids.afterEnd(); mark++)
                {
                    ps.addObj((*mark), bi);
                }
                break;
            }
            case 'a': {// добавить объект
                char obj = cin.get();
                cout << "Какое тип объекта вы хотите добавить?" << endl;
                cout << "Точка (p)\nОтрезок (s)\nКруг (с)\n";
                obj = cin.get();
                if (obj == 'p')
                {
                    bi.addObject(OT_POINT);

                }
                else if (obj == 's')
                {
                    bi.addObject(OT_SEGMENT);
                }
                else if (obj == 'c')
                {
                    bi.addObject(OT_CIRCLE);
                }
                else
                    cout << "Unknown command" << endl;
                break;
            }
            case 'l': {// показать идентификаторы объектов
                Array<ID> ids = bi.ReceiveIdObjects();
                for (Array<ID>::Marker mark = ids.init();mark != ids.afterEnd(); mark++)
                {
                    switch (bi.identifyObjTypeByID(*mark))
                    {
                    case OT_CIRCLE:
                        cout << "Окружность: " << (*mark).getID() << '\n';
                        break;
                    case OT_POINT:
                        cout << "Точка: " << (*mark).getID() << '\n';
                        break;
                    case OT_SEGMENT:
                        cout << "Прямая: " << (*mark).getID() << '\n';
                        break;
                    case OT_ERROR:
                        throw;
                    }
                }
                system("pause");
                break;
            }
            case 'r': {// добавить требование
                char rq;
                cout << "Какое требование вы хотите добавить?" << endl;
                cout << "Параллельность (p)\nОртогональность (о)\nЗафиксировать расстояние между объектами (d)\nГруппировка (g)\nСовмещение (c)\n";
                cin >> rq;
                if (rq == 'p')
                {
                    cout << "Введите идентификаторы двух прямых:" << endl;
                    size_t ID1, ID2;
                    Array<ID> arr;
                    while(true) {
                        cout << "Первая прямая: ";
                        cin >> ID1;
                        Array<ID> IDs = bi.ReceiveIdObjects();
                        size_t i = 0;
                        while (ID1 != IDs[i].getID())
                        {
                            i++;
                        }
                        arr.add(IDs[i]);
                        if (bi.identifyObjTypeByID(IDs[i]) == OT_SEGMENT)
                        {
                            break;
                        }
                        cout << "Это не прямая\n";
                    }
                    while (true) {
                        cout << "Вторая прямая: ";
                        cin >> ID2;
                        Array<ID> IDs = bi.ReceiveIdObjects();
                        size_t i = 0;
                        while (ID2 != IDs[i].getID())
                        {
                            i++;
                        }
                        arr.add(IDs[i]);
                        if (bi.identifyObjTypeByID(IDs[i]) == OT_SEGMENT)
                        {
                             break;
                        }
                        cout << "Это не прямая\n";
                    }
                    bi.addRequirement(arr, RT_PARALLEL);
                    bi.solveComplexReq();
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
                return 0;
            }
            }
        }
    }
    catch (...) {
        std::cout << "Achtung!!!" << std::endl;
    }
    return 0;
}
