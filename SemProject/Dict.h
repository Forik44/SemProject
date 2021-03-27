#pragma once
#include "Array.h"
template<typename  Chemu, typename Chto> class UniDict
{
private:
    struct Para {
        Chemu che;
        Chto cht;
    };
    Array<Para> m_storage;
    size_t size;
    friend class Marker;
public:
	UniDict();
    void add(Chemu che, Chto cht);
    Chto& operator[](Chemu che);
    class Marker
    {
    private:
        typename Array<Para>::Marker mark;
    public:
        friend class UniDict;
        Para& operator*()
        {
            Marker m;
            m.mark = m_storage.init();
            return (*m.mark);
        };
        const Para& operator*() const
        {
            Marker m;
            m.mark = m_storage.init();
            return (*m.mark);
        };
        void operator++()
        {
            /*mark.Elem++;
            mark.Idx++;*/
        };
        void operator++(int)
        {
            /*mark.Elem++;
            mark.Idx++;*/
        };
        bool operator==(const Marker& secondMarker) const
        {
            return /*(this->mark.Elem == secondMarker.mark.Elem && this->mark.Idx == secondMarker.mark.Idx)*/false;
        };
        bool operator!=(const Marker& secondMarker) const
        {
            return /*!(*this == secondMarker)*/false;
        }
        bool canMoveNext()
        {
            return (mark.Idx < mark.markerSize);
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
    Chemu getChemuByIdx(size_t idx)
    {
       /* return m_storage[idx].Chemu;*/
        Chemu che;
        return che;
    }
};

template<typename  Chemu, typename Chto> UniDict<Chemu, Chto>::UniDict()
{
   /* size = 0;
    m_storage = nullptr;*/
};
template<typename  Chemu, typename Chto> void UniDict<Chemu, Chto>::add(Chemu che, Chto cht)
{
	Para newPara;
	newPara.che = che;
	newPara.cht = cht;
    size++;
	m_storage.add(newPara);
}
//template<typename  Chemu, typename Chto> Chto& UniDict<Chemu, Chto>::operator[](Chemu che)
//{
//	Array<Para>::Marker m = m_storage.init();
//	for (; m != m_storage.afterEnd(); m++)
//	{
//		if ((*m).che == che)
//		{
//			return (*m).chto;
//		}
//	}
//	return -1;
//}

