#pragma once
#include "Array.h"
template<typename  Key, typename Value> class UniDict
{
private:
    struct Para 
    {
        Key key;
        Value val;
    };
    Array<Para> m_storage;
    size_t size;
    friend class Marker;
public:
    UniDict()
    {
        size = 0;
    };
    UniDict(const UniDict& original)
    {
        m_storage = original.m_storage;
        size = original.size;
    }
    void add(Key key, Value val);
    Value& operator[](Key key);
    UniDict& operator=(const UniDict& original)
    {
        m_storage = original.m_storage;
        size = original.size;
    }
    class Marker
    {
    private:
        typename Array<Para>::Marker mark;
    public:
        friend class UniDict;
        Para& operator*()
        {
            return (*mark);
        };
        const Para& operator*() const
        {
            return *mark;
        };
        void operator++()
        {
            mark++;
        };
        void operator++(int)
        {
            mark++;
        };
        bool operator==(const Marker& secondMarker) const
        {
            return mark == secondMarker.mark;
        };
        bool operator!=(const Marker& secondMarker) const
        {
            return mark != secondMarker.mark;
        }
        bool canMoveNext()
        {
            return false; //mark != m_storage.afterEnd();
        };
    };
    Marker init()
    {
        Marker m;
        m.mark = m_storage.init();
        return m;
    };
    Marker afterEnd()
    {
        Marker m;
        m.mark = m_storage.afterEnd();
        return m;
    };
    Marker initAfterAddingNewElement()
    {
        Marker ma;
        ma.mark = m_storage.initAfterAddingNewElement();
        return ma;
    };
    size_t getSize()
    {
        return m_storage.getSize();
    }
    bool removeElementByKey(Key k)
    {
        for (int i = 0; i < m_storage.getSize(); i++)
        {
            if ((m_storage[i]).key == k)
            {
                m_storage.removeElementByIdx(i);
                return true;
            }
        }
        return false;
    };
   
};

template<typename  Key, typename Value> void UniDict<Key, Value>::add(Key key, Value val)
{
	Para newPara;
	newPara.key = key;
	newPara.val = val;
    size++;
	m_storage.add(newPara);
}
template<typename Key, typename Value> Value& UniDict<Key, Value>::operator[](Key key)
{
    
	for (typename Array<Para>::Marker m = m_storage.init(); m != m_storage.afterEnd(); m++)
	{
		if ((*m).key == key)
		{
			return (*m).val;
		}
	}

    Value val = 0;
    add(key, val);

    for (typename Array<Para>::Marker m = m_storage.init(); m != m_storage.afterEnd(); m++)
    {
        if ((*m).key == key)
        {
            return (*m).val;
        }
    }
}

