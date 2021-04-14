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
	~Stack()
	{
		for (Node* tmp = First; tmp; tmp = First)
		{
			First = tmp->next;
			delete tmp;
		}
	}
	Stack& operator=(const Stack& original)
	{
		Data* arr = new Data[original.size];

		int i = 0;
		for (Node* ptr = original.First; ptr; ptr = ptr->next,i++)
		{
			arr[i] = ptr->data;
		};

		for (i--; i >= 0; i--)
		{
			push(arr[i]);
		}
		size = original.size;


		delete[] arr;
		return *this;
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