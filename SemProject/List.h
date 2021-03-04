#pragma once

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
    ListElement getElementByIdx(size_t Num) const;
    size_t getSize() const;
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

template<typename ListElement> ListElement List<ListElement>::getElementByIdx(size_t Num) const
{
    if (Num < size)
    {
        Node* tmp;
        for (tmp = first; tmp->idx != Num; tmp = tmp->next);
        return tmp->data;
    }
    else
        exit(1);
};

template<typename ListElement> size_t List<ListElement>::getSize() const
{
    return size;
};

