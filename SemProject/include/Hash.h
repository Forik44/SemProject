
#pragma once

#include <cstdlib>
#include "List.h"
#include "OneSizeArray.h"

template<typename Key, typename Value, const size_t size, typename Translator> class Hash 
{
private:
    struct Para
    {
        Key* key;
        Value* val;
    };
    OneSizeArray< List<Para> > arr;
public:
    Hash()
    {   
        arr = new OneSizeArray(size);
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
            throw 1;
        }
        else
        {
            List<Para>::Marker m = arr[code].init();
            while (m != arr[code].afterEnd())
            {
                if (*(m) == k)
                {
                    break;
                }
                m++;
            }
            if (m != arr[code].afterEnd())
                return (*m)->val;
            else
                throw 1;
        }

    };
    const Value& operator[](Key k)const
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
                if ((*m).key == k)
                {
                    break;
                }
                m++;
            }
            if (m != arr[code].afterEnd())
                return (*m)->val;
            else
                throw 1;
        }

    };

    bool removeElementByKey(Key k)
    {
        Translator tr;
        size_t code = tr.perform(k) % size;

        if (!arr[code].getSize())
        {
            return false;
        }
        else
        {
            List<Para>::Marker m = arr[code].init();
            int idx = 0;
            while (m != arr[code].afterEnd())
            {
                if ((*m).key == k)
                {
                    arr[code].removeElementByIdx(idx);
                    return true;
                }
                idx++;
                m++;
            }
           
            return false;
        }
    };
   
    size_t getSize() const
    {
        return size;
    };
   
   
  
};

