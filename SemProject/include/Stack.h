#pragma once

template<typename Data> class Stack
{
private:
	struct Node
	{
		Node* next;
		Data data;
	};
	Node* First;
	size_t size;

public:
	Stack()
	{
		First = nullptr;
		size = 0;
	}
	const size_t getSize()
	{
		return size;
	}
	const Data check()
	{
		return First->data;
	}
	Data pop()
	{
		if (First == nullptr)
		{
			throw;
		}

		Data res = First->data;

		Node* tmp = First;
		First = First->next;

		size--;
		delete tmp;
		return res;
	}
	void push(Data val)
	{
		Node* tmp = new Node;
		tmp->next = First;
		tmp->data = val;

		First = tmp;

		size++;
	}

};