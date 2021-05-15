#pragma once
#include <cstdlib>

template<typename ListElement> class List
{
private:
    struct Node
    {
        Node* next;
        ListElement data;
        size_t idx;
    };
    size_t size;
    Node* first, * last;
public:
    List();   
    List(const List& original);
    ~List();  
    void add(ListElement val2add);
    ListElement& operator[](size_t idx);
    const ListElement& operator[](size_t idx) const;
    bool removeElementByIdx(size_t Num);
    size_t getSize() const;
    class Marker {
    private:
        Node* marker;
        Node* getNext()const
        {
            if (marker == nullptr ) throw 2;
            return marker->next;
        }
    public:
        friend class List;
        Marker():marker(nullptr){}
        ListElement& operator*()
        {
            if (marker)
                return marker->data;
            else
                throw 2;
        };
        const ListElement& operator*() const
        {
            if (marker)
                return marker->data;
            else
                throw 2;
        };
        bool operator==(const Marker& secondMarker) const{
            return marker == secondMarker.marker;
        }
        bool operator!=(const Marker& secondMarker) const {
            return marker != secondMarker.marker;
        }
        void operator++(){

            marker = getNext();
        };
        void operator++(int){
            marker = getNext();
        };

    };
    List& operator= (const List& list)
    {
        for (size_t i = 0; i < size; i++)
        {
            removeElementByIdx(i);
        }
        for (size_t i = 0; i < list.getSize(); i++)
        {
            add(list[i]);
        }
       
        return *this;

    }
    Marker init()
    {
        Marker Mark;
        Mark.marker = first;
        return Mark;
    };
    Marker afterEnd(){
        return Marker();
    }
    
};

template<typename ListElement> List<ListElement>::List()
{
    first = last = nullptr;
    size = 0;
};
template<typename ListElement> List<ListElement>::List(const List& original)
{
    size = original.size;
    first = last = nullptr;

    size_t tmpSize = 0;

    for (Node* tmpNode = original.first; tmpNode; tmpNode = tmpNode->next, tmpSize++)
    {
        Node* newListNode = new Node;
        newListNode->idx = tmpSize;
        newListNode->data = tmpNode->data;
        newListNode->next = nullptr;
        if (first == nullptr)
            first = last = newListNode;
        else
        {
            last->next = newListNode;
            last = newListNode;
        };
    };
};
template<typename ListElement> List<ListElement>::~List()
{
    for (Node* tmp = first; tmp; tmp = first)
    {
        first = tmp->next;
        delete tmp;
    };
};
template<typename ListElement> void List<ListElement>::add(ListElement val2add)
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
template<typename ListElement> ListElement& List<ListElement>::operator[](size_t idx)
{
    if (idx < size)
    {
        Node* tmp;
        for (tmp = first; tmp->idx != idx; tmp = tmp->next);
        return tmp->data;
    }
    else
       throw 2;
};
template<typename ListElement> const ListElement& List<ListElement>::operator[](size_t idx) const
{
    if (idx < size)
    {
        Node* tmp;
        for (tmp = first; tmp->idx != idx; tmp = tmp->next);
        return tmp->data;
    }
    else
        throw 2;
};
template<typename ListElement> bool List<ListElement>::removeElementByIdx(size_t Num)
{
    if (Num >= size)
        return 0;
    Node* item2BeDeleted;

    if (size == 1)
    {
        item2BeDeleted = first;
        first = last = nullptr;
    }
    else if (Num == 0)
    {
        item2BeDeleted = first;
        first = first->next;
    }
    else
    {
        Node** ptr;
        for (ptr = &first; (*ptr)->next->idx != Num; ptr = &(*ptr)->next);

        item2BeDeleted = (*ptr)->next;
        (*ptr)->next = item2BeDeleted->next;

        if (Num == size - 1)
            last = (*ptr);
    }

    for (Node** tmp = &item2BeDeleted->next; (*tmp); tmp = &(*tmp)->next)
        (*tmp)->idx--;

    delete item2BeDeleted;
    size--;

    return 1;
};
template<typename ListElement> size_t List<ListElement>::getSize() const
{
    return size;
};

