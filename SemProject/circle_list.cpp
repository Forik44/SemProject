
#include "circle_list.h"


CircleList::CircleList()    //constructor
{
    first = last = nullptr;
    size = 0;
};
CircleList::~CircleList()   //destructor
{
    for (Node* tmp = first; tmp; tmp = first)
    {
        first = tmp->next;
        delete tmp;
    };
};
void CircleList::addCircle(Circle val2add)
{
    Node* tmp = new Node;
    tmp->idx = size;
    tmp->data = val2add;
    tmp->next = nullptr;
    if (first == nullptr)
    {
        first = last = tmp;
        size = 1;
    }
    else
    {
        last->next = tmp;
        last = tmp;
        size++;
    }
};
Circle CircleList::getElementByIdx(size_t Num) const
{
    if (Num < size)
    {
        Node* tmp;
        for (tmp = first; tmp->idx != Num; tmp = tmp->next);
        return tmp->data;
    }
    else
        exit(1); //Error
};
size_t CircleList::getSize() const
{
    return size;
};
