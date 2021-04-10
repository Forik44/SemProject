#pragma once
#include "List.h"

template<typename Element> class Queue
{
private:
	List<Element> list_storage;
	size_t size;
public:
	Queue();
	Queue(const Queue& original);
	~Queue();
	void push(Element val2add);
	Element pull();

};
template<typename Element> Queue<Element>::Queue()
{
	size = 0;
	list_storage = nullptr;
};
template<typename Element> Queue<Element>::Queue(const Queue<Element>& original)
{
	size = original.size;
	if (size == 0)
		list_storage = nullptr;
	else
		list_storage = original.list_storage;

};
template<typename Element> Queue<Element>::~Queue()
{
	while (list_storage.getSize() != 0)
	{
		list_storage.removeElementByIdx(0);
	}
};
template<typename Element> void Queue<Element>::push(Element val2add)
{
	list_storage.add(val2add);
	size++;
}
template<typename Element> Element Queue<Element>::pull()
{
	if (size == 0)
		throw Ahtung("Нечего pullit'");
	list_storage.getElementByIdx(0);
	list_storage.removeElementByIdx(0);
	size--;
}