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

