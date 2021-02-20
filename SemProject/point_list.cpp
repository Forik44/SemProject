#include "point_list.h"
#include "objects.h"
#include <iostream>

    PointList::PointList()
    {
        size = 0;
        first->next = nullptr;
        first->data = nullptr;
    } 
    PointList::~PointList() //destructor
    {
        for (Node* tmp = first; tmp; tmp = first)
        {
            first = tmp->next;
            delete tmp;
        };
    };
    void PointList::addPoint(Point &val2add)
    {
        if (size == 0)
        {
            size = 1;
            first->data = &val2add;
            first->next = new PointList;
        }
        else
        {
            PointList* marker = next;
            for (size_t i = 0; i < size-1; i++)
            {
                marker = marker->next;
            }
            marker->data = &val2add;
            marker->next = new PointList;
            size++;
        }
    }
    size_t PointList::getSize() const { return size; }
    Point PointList::getElementByInd(size_t index) const
    {
        if (size <= index)
        {
            std::cout << "Неверный индекс";
            exit(1);
        }
        if (index == 0)
            return *data;
        PointList* marker = next;
        for (size_t i = 1; i < index; i++)
        {
            marker = marker->next;
        }
        return *marker->data;
    }
