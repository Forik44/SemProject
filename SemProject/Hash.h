
#pragma once

#include <cstdlib>
#include "List.h"
#include "OneSizeArray.h"

template<typename Key, typename Value, const size_t size, typename Translator> class Hash 
{
private:
    struct Para
    {
        Key key;
        Value val;
    };
    OneSizeArray< List<Para> > arr(size);
public:
    Hash()
    {   

    };
   // Array(const Array& original);
    ~Hash()
    {
        
    };
    void add(Key k, Value v)
    {
        Translator tr;
        size_t code = tr.perform(k) % size;
        Para p;
        p.key = k;
        p.val = v;
        arr[code].add(p);
    };
    Value& operator[](Key k)
    {
        Translator tr;
        size_t code = tr.perform(k) % size;

        if (!arr[code].getSize())
        {
            return NULL;
        }
        else
        {
            List<Para>::Marker m = arr[code].init();
            while (m != arr[code].afterEnd())
            {
                if(*(m))
                m++;
            }
        }

    };
    const Value& operator[](Key k)const
    {
        Translator tr;
        size_t code = tr.perform(k) % size;

        Node* tmp = data[code];

        while (tmp->key != k)
        {
            tmp = tmp->next;
            if (!tmp)
                return NULL;
        };

        return tmp->val;

    };

    bool removeElementByKey(Key k)
    {

    };
    /* removeByMarker(const Marker&);*/
    size_t getSize() const
    {
        return size;
    };
   
    Array& operator= (const Array& arr)
    {

        for (size_t i = 0; i < size; i++)
        {
            removeElementByIdx(i);
        }
        for (size_t i = 0; i < arr.getSize(); i++)
        {
            add(arr[i]);
        }
        size = arr.size;
        return *this;
    }
  
};

