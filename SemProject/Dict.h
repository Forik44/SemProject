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
    struct marker
    {
        Para* Elem;
        size_t Idx;
        size_t markerSize;
    };
    size_t size;
    friend class Marker;
public:
	Dict();
    void add(Chemu che, Chto cht);
    Chto& operator[](Chemu che);

    class Marker
    {
        marker mark;
    public:
        friend class UniDict;
        Para& operator*()
        {
            return *mark.Elem;
        };
        const Para& operator*() const
        {
            return *mark.Elem;
        };
        void operator++()
        {
            mark.Elem++;
            mark.Idx++;
        };
        void operator++(int)
        {
            mark.Elem++;
            mark.Idx++;
        };
        bool operator==(const Marker& secondMarker) const
        {
            return (this->mark.Elem == secondMarker.mark.Elem && this->mark.Idx == secondMarker.mark.Idx);
        };
        bool operator!=(const Marker& secondMarker) const
        {
            return !(*this == secondMarker);
        }
        bool canMoveNext()
        {
            return (mark.Idx < mark.markerSize);
        };
        void setMarkerSize(size_t size)
        {
            mark.markerSize = size;
        }

    };

    Marker init()
    {
        Marker ma;
        ma.setMarkerSize(size);
        ma.mark.Elem = m_storage.init();
        ma.mark.Idx = 0;
        return ma;
    };
    Marker afterEnd()
    {
        Marker ma;
        ma.setMarkerSize(size);
        ma.mark.Elem = m_storage.init() + size;
        ma.mark.Idx = ma.mark.markerSize;
        return ma;
    };
    Marker initAfterAddingNewElement()
    {
        Marker ma;
        ma.setMarkerSize(size);
        ma.mark.Elem = m_storage.init() + size - 2;
        ma.mark.Idx = size - 2;
        return ma;
    };

    Marker find(Chemu);

};

template<typename  Chemu, typename Chto> void UniDict<Chemu, Chto>::add(Chemu che, Chto cht)
{
	Para newPara;
	newPara.che = che;
	newPara.cht = cht;
	m_storage.add(newPara);
}

template<typename  Chemu, typename Chto> Chto& UniDict<Chemu, Chto>::operator[](Chemu che)
{
	Array<Para>::Marker m = m_storage.init();
	for (; m != m_storage.afterEnd(); m++)
	{
		if ((*m).che == che)
		{
			return (*m).chto;
		}
	}
	return 1;
}


