#pragma once
template<typename  Chemu, typename Chto> class Dict
{
public:
	Dict();
	void add(Chemu che, Chto cht);
	Chto get(chemu);

private:
	struct Para {
		Chemu che;
		Chto cht;
	};
	Array<Para> m_storage;

};

template<typename  Chemu, typename Chto> void Dict<Chemu, Chto>::add(Chemu che, Chto cht)
{
	
      m_storage,
}

