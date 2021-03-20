#pragma once
#include "Array.h"
template<typename  Chemu, typename Chto> class UniDict
{
public:
	Dict();
	class Marker {

	};
	void add(Chemu che, Chto cht);
	Marker find(Chemu);
	Chto& operator[](Chemu che);

private:
	struct Para {
		Chemu che;
		Chto cht;
	};
	Array<Para> m_storage;

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


