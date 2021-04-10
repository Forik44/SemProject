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
	UniDict();
    void add(Key key, Value val);
    Value& operator[](Key key);
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
    bool removeElementByIdx(size_t idx)
    {
        return m_storage.removeElementByIdx(idx);
    }
    Key getChemuByIdx(size_t idx)///////////////////////////////////////////////////////////////////////
    {
        Key key;
        return key;
    }
};

template<typename  Key, typename Value> UniDict<Key, Value>::UniDict()
{
    size = 0;
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
    typename Array<Para>::Marker m = m_storage.init();
	for (; m != m_storage.afterEnd(); m++)
	{
		if ((*m).key == key)
		{
			return (*m).value;
		}
	}
	return -1;
}

